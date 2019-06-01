


// NOTE : Data written to the write end of the pipe is buffered by the  kernel until it is read from
// the read end of the pipe

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include "color.h"
//#define MSG "I am Mahakaal\n"
#define MSG "I am Mahakaal"

int main()
{
	pid_t id;

	int fd[2];
	pipe(fd);

	id = fork();

	// I am the parent block
	if (id > 0)
	{
		int status;
		printf(GREEN"[+]"RESET" In parent block, id : %d\n", id);
	
		// Write to the pipe
		write(fd[1], MSG, sizeof(MSG));
		waitpid(id, &status, 0);			// Wait for the child to finish
	}

	// I am the child block, child process executes concurrently with parent process.
	else if (id == 0)
	{
		printf(YELLOW"[+]"RESET" In child block, id: %d\n", id);
				
		char character;
		int bytes_read;

		// Read bytes one at a time from the pipe and put it to console
		while ( (bytes_read = read(fd[0], &character, 1)) > 0 )
		{
			putchar(character);
			// printf("\n");			// This flushes the buffer, otherwise the output remains in
										// the kernel buffer and never gets flushed to stdout since
										// the program never fills the whole kernel buffer, neither
										// does it exits (because of while loop) and it does'nt even
										// explicitly flush out the buffer. It just waits to read
										// for next character in the pipe.
			fflush(stdout);
		}
	}	

	else if (id < 0)
	{
		printf(RED"[-]"RESET" ERROR : Not able to fork, exiting ...\n");
	}

return 0;
}
