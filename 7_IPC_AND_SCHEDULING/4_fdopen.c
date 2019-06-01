// An error while using fdopen() : Invalid argument
// I need to fix it !!

// NOTE : Data written to the write end of the pipe is buffered by the  kernel until it is read from
// the read end of the pipe

#define _POSIX_SOURCE				// To use fdopen in -std=c99 (for compatibility with C standard)
									// or we can use -std=gnu99 to go for POSIX and get rid of C std)


#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#include "color.h"

#define NAME "Mahakaal"
#define PASSION "Exploit Researcher"


int main(int argc, char **argv)
{
	char *filename = argv[1];
	
	// Error: Usage
	if (argc != 2)
	{
		fprintf(stderr, RED"[-]"RESET" Usage: %s <filename>\n", argv[0]);
		exit(0x10);
	}


	// open file and obtain its file descriptor
	int fd = open( filename , O_CREAT, S_IRUSR | S_IWUSR);
	if (fd == -1)
	{
		perror(RED"open ");
		exit(0x11);
	}
	fprintf(stdout, GREEN"[+]"RESET" file descriptor: %d\n", fd);


	// open file descriptor via file pointer.
	FILE *fptr = fdopen(fd, "r+");
	if (fptr == NULL)
	{
		perror(RED"fdopen ");
		exit(0x12);
	}	


	// Write into file
	fprintf(fptr, GREEN"[+]"RESET" Name : %s => %s\n", NAME, PASSION);
	

	// Read content of the file and print it to stdout
	char buffer[1000];
	fread(buffer, 12+8+18, 1, fptr);
	fprintf(stdout, GREEN"[+]"RESET" Read file : "YELLOW"%s\n", buffer);
	fclose(fptr);

	
return 0;
}
