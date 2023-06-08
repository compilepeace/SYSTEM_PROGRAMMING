/*
	Linker = Merger + Locator

	This script is passed to the build-toolchain (specifically linker component of
	compiler-toolchain) and is used to provide instructions on how to build our final software 
	application via multiple object files (i.e. stitching multiple *.o files into single binary).
	This is done by instructing GNU liker (ld) on -
	- how to merge various object files into final executable.
	- assign absolute addresses (or fix references) to various symbols (sections, data, code etc).
*/

/*
	APPLICATION ENTRY POINT
	The processor doesn't understand ELF file format, it will start its execution from the address
	specified at 2nd entry in vector table (i.e. address of RESET_Handler present in FLASH ROM).
	Therefore, providing entry point via ENTRY linker command has no use other than for debugging
	purposes as such info. is consumed by GDB helping it to break at entry point.
*/
ENTRY(Reset_Handler)

/*
	MEMORY command describes the memory regions available to the program.

	Here, we describe to the linker, the physical memory regions avaialable inside the MCU. 
	We can define whatever portion of physical memory we want our program to use.
	For instance - we are using FLASH/ROM to store code and SRAM to store data.
*/
MEMORY
{
	FLASH(rx): ORIGIN = 0x08000000, LENGTH = 1024K
	SRAM(rw): ORIGIN = 0x20000000, LENGTH = 128K 
}

__max_heap_size = 0x400;	/* A linker symbol declaration . NOT a variable !! */
__max_stack_size = 0x200;	/* A linker symbol declaration . NOT a variable !! */

/*
	SECTIONS command is used to create 'output sections'.
	Each output section describes the merge content and location information for section.
*/
SECTIONS
{
	/*
		To decide where you wish to store .XXX section in memory you have to mention 2 memory
		regions - VMA (virtual memory address) & LMA (load memory address), before that ask 
		yourself a few questions -
		- Do you relocate .XXX section ?
			= If YES, it cannot be stored in FLASH memory region as it is being used as Read-Only,
			  therefore no relocations/fixups possible there
			= If NO, this section can reside in FLASH.

		Now, the linker will generate absolute addresses (both virtual and load) for the output 
		section which will fall in the memory region described by 'VMA' and 'LMA' below.

		NOTE: VMA describes memory address during runtime whereas LMA describes memory address
			  where 'block-of-bytes' is flashed. 
		NOTE: location counter (.) always tracks VMA (runtime address), NOT LMA.
	*/
	.text :
	{
		/* wildcard (*) asking the linker to merge .text section of all input *.o files */
		*(.isr_vector)
		*(.text)
		*(.text.*)
		*(.rodata)
		*(.rodata.*)
		*(.init)
		*(.fini)
		. = ALIGN(4);	/* align the location counter */
		_etext = .;		/* assigns VMA for end of .text section to the symbol '_etext'  */ 	
	}> FLASH			/* means both VMA and LMA fall in FLASH memory region */
	/* >'VMA' AT>'LMA' */

	_la_data = LOADADDR(.data);
	.data :
	{
		/* we want to copy .data section from FLASH ROM to SRAM at runtime (done by startup.c) */
		_sdata = .;		/* assigns VMA for start of .data section, i.e. 0x20000000 */
		*(.data)
		*(.data.*)
		*(.init_array)
		*(.fini_array)
		. = ALIGN(4);	/* align the location counter */
		_edata = .;		/* assigns VMA for end of .data section to the symbol '_edata' */
	}> SRAM AT> FLASH	/* means will be present AT FLASH (LMA),at runtime found in SRAM (VMA)  */
	/* >'VMA' AT>'LMA' */

	.bss :
	{
		_sbss = .;		/* assigns VMA for start of .bss section to the symbol '_sbss' */
		__bss_start__ = _sbss;		/* required by newlibc-nano */
		*(.bss)
		. = ALIGN(4);	/* align the location counter */
		_ebss = .;		/* assigns VMA for end of .bss section to the symbol '_ebss' */
		__bss_end__ = _ebss;		/* required by newlibc-nano */
		. = ALIGN(4);
		end = .;		/* required by _sbrk():syscalls.c */
		__end__ = end;	/* to make rdimon_nano.a (required for semi-hosting) happy */
	}> SRAM					/* this doesn't have a LMA as it doesn't take up space in FLASH ROM */
}
