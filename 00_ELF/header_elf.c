#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>


#include "color.h"



#define PAGE_SIZE sysconf(_SC_PAGE_SIZE)
#define TESTING_FILE "./testing_binary"



/*

#	Roadmap to a successful parasitic code injection

=>	fd = Open file in (O_RDWR mode)
=>	Get page size as default used by system - sysonf(_SC_PAGE_SIZE)
=>	mmap file into memory
	->	void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
		->	addr	= NULL (kernel chooses the base address to map)
		->	length	= file_size
		->	prot	= PROT_WRITE (Mapped pages may be written)
		->	flags	= MAP_PRIVATE
		->	fd		= file descriptor to opened file above (1st step)
		->	offset	= 0
	->
=>	Parse ELF header
=>
*/
int main(int argc, char **argv)
{
	char *pathname = argv[1];
	struct stat statbuf;


	if (argc < 2)
	{
		fprintf(stdout, RED"[-]"RESET" Usage: %s <filename>\n", argv[0]);
		exit(0x16);
	}

	// To get the size of binary pointed to by 'pathname'
	if ( lstat(pathname, &statbuf) != 0 )
	{
		perror(RED"[-]"RESET" lstat():");
		exit(0x10);
	}
	long int file_size = statbuf.st_size;
	fprintf(stdout, GREEN "[+]"RESET" PAGE_SIZE\t\t\t\t : %ld bytes\n", PAGE_SIZE);
	fprintf(stdout, GREEN"[+]"RESET" %s (size on disk)\t : %ld bytes\n", pathname, file_size);


	int fd = open(pathname, O_RDWR);
	if (fd == -1)
	{
		perror(RED"[-]"RESET" open():");
		exit(0x11);
	}
	//fprintf(stdout, "Opened %s in O_RDWR mode\n", pathname);


	void *map_address = mmap(NULL, statbuf.st_size, PROT_WRITE, MAP_PRIVATE, fd, 0);
	if (map_address == MAP_FAILED)
	{
		perror("mmap():");
		exit(0x12);
	}


	fprintf(stdout, YELLOW"[+]"RESET" SUCCESSFULLY MAPPED %s @ "RED"%p\n\n"RESET, pathname, map_address);

	// Typecast the (void *) into (Elf64_Ehdr *)
	//parse_elf_header( (Elf64_Ehdr *)map_address );


	Elf64_Ehdr *binary_header = map_address;

	// 1st 4 bytes : Check for ELF file format
	if (
		binary_header->e_ident[EI_MAG0] == ELFMAG0 &&		// ELFMAG0 is MACRO for 0x7f
		binary_header->e_ident[EI_MAG1] == ELFMAG1 &&		// ELFMAG1 is MACRO for 'E'
		binary_header->e_ident[EI_MAG2] == ELFMAG2 &&		// ELFMAG2 is MACRO for 'L'
		binary_header->e_ident[EI_MAG3] == ELFMAG3			// ELFMAG3 is MACRO for 'F'
	)	fprintf(stdout, GREEN"[+]"RESET" Filetype \t\t\t\t : ELF\n");
	else
	{
		fprintf(stdout, RED"[-]"RESET" Not an ELF\n");
		exit(0x13);
	}


	// 5th byte : Check for 32-bit or 64-bit class of binary
	if (binary_header->e_ident[EI_CLASS] == ELFCLASS32) fprintf(stdout, GREEN"[+]"RESET" Class \t\t\t\t : 32-bit binary\n");
	else if (binary_header->e_ident[EI_CLASS] == ELFCLASS64) fprintf(stdout, GREEN"[+]"RESET" Class \t\t\t\t : 64- bit binary\n");
	else fprintf(stdout, RED"[-]"RESET" Not a valid class of ELF");

	// 6th byte : check for data encoding
	if (binary_header->e_ident[EI_DATA] == ELFDATA2LSB) fprintf(stdout, GREEN"[+]"RESET" Data Encoding \t\t\t : Little-endian \n");
	else if (binary_header->e_ident[EI_DATA] == ELFDATA2MSB) fprintf(stdout, GREEN"[+]"RESET" Data Encoding \t\t\t : Big-endian\n");
	else fprintf(stdout, RED"[-]"RESET" Unknown data encoding \n");

	// 7th byte : Check for version number
	if (binary_header->e_ident[EI_VERSION] == EV_CURRENT) fprintf(stdout, GREEN"[+]"RESET" Version \t\t\t\t : Current version \n");
	else fprintf(stdout, RED"[-]"RESET" Invalid version\n");

	// 8th byte : Check for operating system ABI for which the object is targetted
	if (binary_header->e_ident[EI_OSABI] == ELFOSABI_SYSV) fprintf(stdout, GREEN"[+]"RESET" Target \t\t\t\t : Unix System V ABI\n");
	else if (binary_header->e_ident[EI_OSABI] == ELFOSABI_HPUX) fprintf(stdout, GREEN"[+]"RESET" Target \t\t\t\t : HP-UX ABI\n");
	else if (binary_header->e_ident[EI_OSABI] == ELFOSABI_NETBSD) fprintf(stdout, GREEN"[+]"RESET" Target \t\t\t\t : NetBSD ABI\n");
	else if (binary_header->e_ident[EI_OSABI] == ELFOSABI_LINUX) fprintf(stdout, GREEN"[+]"RESET" Target \t\t\t\t : Linux ABI\n");
	else if (binary_header->e_ident[EI_OSABI] == ELFOSABI_SOLARIS) fprintf(stdout, GREEN"[+]"RESET" Target \t\t\t\t : Solaris ABI\n");
	else if (binary_header->e_ident[EI_OSABI] == ELFOSABI_IRIX) fprintf(stdout, GREEN"[+]"RESET" Target \t\t\t\t : IRIX ABI\n");
	else if (binary_header->e_ident[EI_OSABI] == ELFOSABI_FREEBSD) fprintf(stdout, GREEN"[+]"RESET" Target \t\t\t\t : FreeBSD ABI\n");
	else if (binary_header->e_ident[EI_OSABI] == ELFOSABI_TRU64) fprintf(stdout, GREEN"[+]"RESET" Target \t\t\t\t : TRU64 UNIX ABI\n");
	else if (binary_header->e_ident[EI_OSABI] == ELFOSABI_ARM) fprintf(stdout, GREEN"[+]"RESET" Target \t\t\t\t : ARM arch. ABI\n");
	else if (binary_header->e_ident[EI_OSABI] == ELFOSABI_STANDALONE) fprintf(stdout, GREEN"[+]"RESET" Target \t\t\t\t : Stand-alone (embedded) ABI\n");
	else fprintf(stdout, RED"[-]"RESET" UNIX System V ABI\n");


	// Check for object file type
	if (binary_header->e_type == ET_DYN)
		fprintf(stdout, GREEN"[+]"RESET" Filetype \t\t\t\t : A shared object\n");
	else if (binary_header->e_type == ET_REL)
        fprintf(stdout, GREEN"[+]"RESET" Filetype \t\t\t\t : A relocatable file\n");
	else if (binary_header->e_type == ET_EXEC)
		fprintf(stdout, GREEN"[+]"RESET" Filetype \t\t\t\t : An executable file\n");
	else if (binary_header->e_type == ET_CORE)
		fprintf(stdout, GREEN"[+]"RESET" Filetype \t\t\t\t : A core file\n");
	else
		fprintf(stdout, RED"[+]"RESET" Filetype \t\t\t\t : An unknown type\n");


	// Check only for Intel 80386 and x86-64 binary types
	if (binary_header->e_machine == EM_386)
        fprintf(stdout, GREEN"[+]"RESET" Compiled for \t\t\t : Intel 80386\n");
	else if (binary_header->e_machine == EM_X86_64)
        fprintf(stdout, GREEN"[+]"RESET" Compiled for \t\t\t : AMD x86-64\n");
	else
		fprintf(stdout, RED"[+]"RESET" Compiled for x86 or x86-64 \n");


	// Entry point
	Elf64_Addr entry_point = (Elf64_Addr ) binary_header->e_entry;
	fprintf(stdout, GREEN"[+]"RESET" Entry point \t\t\t : 0x%lx\n", entry_point);


	// Program Header Table's  offset
	Elf64_Off phdr_offset = (Elf64_Off ) binary_header->e_phoff;
	fprintf(stdout, GREEN"[+]"RESET" Phdr @ offset \t\t\t : %ld bytes (from the beginning of the file)\n", phdr_offset);


	// Section Header Table's offset
	Elf64_Off shdr_offset = (Elf64_Off ) binary_header->e_shoff;
    fprintf(stdout, GREEN"[+]"RESET" Shdr @ offset \t\t\t : %ld bytes (from the beginning of the file)\n", shdr_offset);


	// Processor specific flags associated with file
	int flags = (int )binary_header->e_flags;
	fprintf(stdout, GREEN"[+]"RESET" Flags associated with the file \t : 0x%x\n", flags);


	// ELF header's size
	int elf_header_size = (int )binary_header->e_ehsize;
	fprintf(stdout, GREEN"[+]"RESET" ELF header size \t\t\t : %d bytes\n", elf_header_size);


	// Size of 1 entry in PHT
	int pht_entry_size = (long int )binary_header->e_phentsize;
	fprintf(stdout, GREEN"[+]"RESET" PHT entry size \t\t\t : %d\n", pht_entry_size);


	// Number of entries in PHT
	int pht_entries_count = (int )binary_header->e_phnum;
	fprintf(stdout, GREEN"[+]"RESET" Number of PHT entries \t\t : %d\n", pht_entries_count);


	// Size of section headers
	int shdr_size = (int )binary_header->e_shentsize;
	fprintf(stdout, GREEN"[+]"RESET" Size of section headers \t\t : %d\n", shdr_size);

	// Number of section headers
	int shdr_entries_count = binary_header->e_shnum;
	fprintf(stdout, GREEN"[+]"RESET" Number entries in SHT \t\t : %d\n", shdr_entries_count);

	// SHT Index of entry associated with section named - string table
	int sht_string_index = binary_header->e_shstrndx;
	fprintf(stdout, GREEN"[+]"RESET" Section Header string table index \t : %d\n", sht_string_index);



	// =-=-=-=- PARSING SECTION HEADERS	-=-=-=-= 
	Elf64_Shdr *section_header_table = map_address + binary_header->e_shoff;

	// A pointer to 1st byte of section_header_table
	Elf64_Shdr *ptr = section_header_table;
	char *byte_ptr = (char *)ptr;

}
