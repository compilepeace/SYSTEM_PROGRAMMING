// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : This program uses mmap to map a file in persistent storage into memory and how any 
//				 alteration to that mapped memory affects the persistent storage. 


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "color.h"



int main(int argc, char *argv[])
{

    // Check for command line arguments
    if (argc < 2)
    {
        fprintf(stderr, RED"[-]"YELLOW" Usage: %s <FILE_PATH>\n", argv[0]);
        exit(0x10);
    }

	int size = 40 * sizeof(int );

	
	// open the file
	int fd = open(argv[1], O_CREAT | O_RDWR | O_TRUNC, 0600 );


	// mmap the file into memory 
	void *address = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	fprintf(stdout, GREEN"[+]"RESET" File mapped at : "GREEN"%p\n\n", address);

	
	// Mark the length of file with lseek and write an "A" at the end of file
	lseek(fd, size, SEEK_SET);
	write(fd, "A", 1);


	// Set a  pointer to mapped memory location
	int *addr = (int *)address;


	// Place 0xdeadbeef 40 times	
	for ( ; addr < (int *)(address + size); (int *)++addr)
	{	
		*addr = 0xdeadbeef;
		fprintf(stdout, GREEN"[+]"RESET" Now writing at: "CYAN"%p \n", addr);
	}


	fprintf(stdout, GREEN"[+] Unmapping...\n");
	munmap(address, size);
	
return 0;
}

