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
=>  Identify .text section 
=>  parse through SHT and extract offset and size of .text section
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

//---------------------------------------------------------------------------------------------------------


	// PROGRAM HEADER TABLE PARSE
	Elf64_Off phdr_offset;
	size_t phdr_entry_size;
	size_t phdr_count;
	
	Elf64_Phdr *elf_phdr_iterator;


    // Load PHT offset(in pht_offset) and no. of headers (entries) in PHT (in phdr_count) and size of
    // each header(entry) in PHT (in phdr_size).
    elf_header 		= (Elf64_Ehdr *)map_address;
	
	phdr_offset 	= elf_header->e_phoff;
	phdr_entry_size = elf_header->e_phentsize;
	phdr_count		= elf_header->e_phnum; 


	elf_phdr_iterator = (Elf64_Phdr *)(map_address + phdr_offset);


	// Iterate over PHT (All Phdr Entries)
	int iter;
	for (iter = 0; iter < phdr_count; ++iter)
	{
		printf("%dth phdr offset : 0x%lx\n", iter, elf_phdr_iterator->p_offset);
		++elf_phdr_iterator;
	}
}
