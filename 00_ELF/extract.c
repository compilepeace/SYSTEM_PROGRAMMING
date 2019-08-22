#include <stdio.h>
#include <elf.h>
#include <sys/mman.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <unistd.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>


#include "color.h"



#define PAGE_SIZE sysconf(_SC_PAGE_SIZE)
#define TESTING_FILE "./testing_binary"



/*

#   Roadmap to a successful parasitic code injection

=>  fd = Open file in (O_RDWR mode)
=>  Get page size as default used by system - sysonf(_SC_PAGE_SIZE)
=>  mmap file into memory
    ->  void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);
        ->  addr    = NULL (kernel chooses the base address to map)
        ->  length  = file_size
        ->  prot    = PROT_WRITE (Mapped pages may be written)
        ->  flags   = MAP_PRIVATE
        ->  fd      = file descriptor to opened file above (1st step)
        ->  offset  = 0
    ->
=>  Parse ELF header and extract sht_offset(e_shoff) and no. of Shdrs(e_shnum)
=>	Identify .text section 
=>	parse through SHT and extract offset and size of .text section
*/

int main(int argc, char **argv)
{
    char *pathname = argv[1];
    struct stat statbuf;
	
	Elf64_Ehdr *elf_header; 
		Elf64_Off sht_offset;
		Elf64_Shdr *elf_shdr;
		size_t shdr_count;
		size_t shdr_entry_size;
			char *elf_shstrtab;
			Elf64_Off end_offset_of_elf;	

	
	int i=0;


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



	// Load SHT offset(in sht_offset) and no. of headers (entries) in SHT (in shdr_count) and size of
	// each header(entry) in SHT (in shdr_size).
	// Also load address of .shstrtab (mmaped into memory) to identify section names (.text section).
	// elf_shstrndx - section header string table index
	elf_header = (Elf64_Ehdr *)map_address;
	sht_offset = elf_header->e_shoff;
	shdr_count = elf_header->e_shnum;
	shdr_entry_size  = elf_header->e_shentsize;

	//elf_shstrndx = elf_header->e_shstrndx;		

	
	// GOALS - 
	// 		Parse the SHT and identify .text section.
	// 		Extract offset and size of .text section.	
	// Point to the last entry in SHT and parse backwards where last entry is that of .shstrtab
	end_offset_of_elf = (sht_offset + shdr_count * shdr_entry_size);
	elf_shdr = (Elf64_Shdr *)(map_address + end_offset_of_elf - sizeof(Elf64_Shdr));
	//elf_shdr = (Elf64_Shdr *)(map_address + end_offset_of_elf );
	

	// =-=--=-==---=-=-=--=--=-==--=-=--=---===-====-=-=-=-==-=-=-=-=-=-=-=-==--=-==-=
	// These 2 declarations must be global in order to use them into other functions
	Elf64_Off text_section_offset;
	size_t text_section_size;
	// =-=-=-=-=-=-=-=-=-=-===-=-==-=-=-==-=-==-=-=-=-==-=-==-=-==-=-=-==-=-==-=-==-=

	// To store all section headers (entries)
	// Parse SHT in opposite direction (from bottom to up) where last section is .shstrtab and we
	// get an offset to it (through which we can access section names).
	// Avoid 1st section entry (which is always NULL)
	Elf64_Shdr shdr[shdr_count];
	for( i = 0 ; i < (shdr_count-1) ; ++i)
	{
		// elf_shdr->sh_offset
		int section_name_offset = elf_shdr->sh_name;
		

		// Means this is the last entry - i.e. of .shstrtab section
		if (i == 0) {
			
			// Address to character array storing section names
			elf_shstrtab = (char *)(map_address + elf_shdr->sh_offset);

			printf("Iterating over : %s\n", (char *)(elf_shstrtab + section_name_offset ));
		}

		else {
			
			printf("Iterating over : %s\n", (char *)(elf_shstrtab + section_name_offset));
			char *section_name = (char *)(elf_shstrtab + section_name_offset);
			if ( strncmp(".text", section_name, 5) == 0 )
			{
				text_section_offset = elf_shdr->sh_offset;
				text_section_size = elf_shdr->sh_size;
				printf(".text section found @offset : 0x%lx, size : 0x%lx\n", text_section_offset, text_section_size);
			}
		}

		// Point to next Shdr entry
		--elf_shdr;
	}

}
