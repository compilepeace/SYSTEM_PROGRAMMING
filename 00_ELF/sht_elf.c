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




    int i;
	Elf64_Ehdr *binary_header = (Elf64_Ehdr *)map_address;

    printf("Offset of SHT from starting of file : %ld\n", binary_header->e_shoff);
    printf("Number of section headers/entries in SHT: %d\n", binary_header->e_shnum);
    printf("Size of each section entry : %d bytes\n", binary_header->e_shentsize);



	// Get to the starting of SHT or point to the first entry in SHT (of the file opened in memory)
	Elf64_Shdr *sht_entry = (Elf64_Shdr *)(map_address + binary_header->e_shoff);
// SHT_entry_type_ptr = address_of_first_byte_of_file (in memory) + offset_to_SHT
	
	// Address of .shstrtab (section header string table index)

	
	Elf64_Off shstrtab_offset=0;
	
	// This array will store the index for the section names (present in .shstrtab section)
	int section_name_offsets[binary_header->e_shnum] ;


	int shstrtab_size=0;

	printf("(Elf64_Shdr *)sht pointing to the first entry of SHT (in memory) @ %p\n", (void *)sht_entry);
	printf("fukc");	
	for (i = 0; i < binary_header->e_shnum; ++i)
	{
		//printf("Address of section (of current entry) is : 0x%x at addr %p\n", sht->sh_addr,  sht);
		printf("[ndx] : %d\n", sht_entry->sh_name);	
		section_name_offsets[i] = sht_entry->sh_name;
	
			// If we are parsing the last entry, store the offset of .shstrtab section
			if (i == (binary_header->e_shnum - 1))
			{
				shstrtab_offset = sht_entry->sh_offset;		// offset at which the section starts
				shstrtab_size = sht_entry->sh_size;			// size of section(section names buffer)		
				printf("shstrtab_size : %d\n", shstrtab_size);
				printf("shstrtab_offset : %d\n", shstrtab_offset);
			}
		// get to the next entry in SHT
		++sht_entry;
	}


	printf(".shstrtab is at offset : %ld\n", shstrtab_offset);

	// In memory, any offset is present at (map_address + offset), so .shstrtab is present at 
	// (map_address + shstrtab_offset)
	char *shstrtab_section_location = (map_address + shstrtab_offset);
	char buffer[shstrtab_size] ;

	// Copy shstrtab_section into our internal buffer 
	strncpy(buffer, shstrtab_section_location, shstrtab_size);
	printf("%s\n", buffer);
/*
	for (i = 0 ; i < binary_header->e_shnum; ++i)
	{
		printf("section_name_offset[%d]: %d\n", i, section_name_offsets[i]);
		printf("Section name at index %d : %s\n", i, section_name_buffer);
		section_name_buffer = section_name_buffer + section_name_offsets[i];
	}	

	// Again parse the SHT for section names
*/	

return 0;
}
