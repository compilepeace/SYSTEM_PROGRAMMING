// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : In this program, the child block writes to the fd[1] end of the pipe and parent 
//				 process reads from the read end fd[0] of the pipe. This program uses fdopen() which
//				 takes in pipe file descriptors as input and open them as a stream (file stream) in
//				 read "r" and write "w" mode so that we can make pipes work with printf/scanf (which
//				 works with streams rather than file descriptors) rather than read/write syscall which
//				 works with file descriptors at low-level.
//				 Therefore, fdopen() prooved out to be a lifesaver by converting file descriptors 
//				 into streams and let the communication of pipes with stream functions happen.


// NOTE : Data written to the write end of the pipe is buffered by the  kernel until it is read from
// the read end of the pipe

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include "color.h"


int main()
{
	int fd[2];

	// Create a pipe
	pipe(fd);

	// Open up pipe file descriptors as file streams to make them work with printf() and scanf()
	// since scanf/printf work with file streams and read/write work with file descriptors.
	FILE *fstream_read = fdopen(fd[0], "r");
	FILE *fstream_write = fdopen(fd[1], "w");

	
	// fork a child process to handle input to the pipe
	pid_t id = fork();


	// Use child to write input to file and parent to write output to file
	// Parent block
	if (id > 0)
	{
		int number = 0;
		
		// If a '\n' is not recieved by scanf() from the pipe, it will hold on forever since scanf()
		// returns only after it recieves a '\n' character.
		fscanf(fstream_read, "Number : %d", &number);	
		fprintf(stdout, GREEN"[+]"RESET" (Parent Block) The score read from pipe : %d --- fd[0]: %d\n", number, fd[0]);		
	}

	// Child block
	else
	{
		int lucky_number = 30;
		fprintf(fstream_write, "Number : %d\n", lucky_number);
		fflush(fstream_write);			// We want our bytes to be sent to the pipe immediately.
		fprintf(stdout, GREEN"[+]"RESET" (Child Block) The score written into pipe : %d --- fd[1]: %d\n", lucky_number, fd[1]);
	}

return 0;
}
