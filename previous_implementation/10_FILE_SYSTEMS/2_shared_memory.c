// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : This program shows how memory is shared between parent and child process simply using
//				 mmap without a file and with the flags 'MAP_ANONYMOUS' and 'MAP_SHARED'. 


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "color.h"



int main(int argc, char *argv[])
{


	// Size of 10 integers
	int size = 10 * sizeof(int);


	// Use mmap without any file descriptor to share memory between processes.
	// void *mmap( void *addr, size_t length, int prot, int flags, int fd, off_t offset);
	void *address = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_ANONYMOUS | MAP_SHARED, -1, 0);	
	
	fprintf(stdout, GREEN"[+]"RESET" Memory mapped at:"CYAN" %p\n", address);


	int *shared = address, i;

	pid_t id = fork();


	// I'm the parent
	if (id > 0)
	{
		for (i=0; i<10; ++i)
		{	
			fprintf(stdout, RESET"[PARENT] Storing "BLUE"%d"RESET" at "CYAN"%p\n"RESET, i, shared);
			*(shared++) = i;
		}
		wait(NULL);
	}

	// I'm the child
	else 
	{
		for (i=0; i<10; ++i)
			fprintf(stdout, RESET"[CHILD] Output => "CYAN"%p"RESET": "BLUE"%d\n", (address + i), *( (int *)address + i)); 
	}


	munmap(address, size);


return 0;
}
