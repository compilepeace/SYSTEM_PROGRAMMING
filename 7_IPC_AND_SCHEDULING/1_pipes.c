// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Decription : This program demonstrates the basic usage of pipe() syscall.
// For theory : Read $ man 7 pipe (documentation)

// HOW PIPES WORK -
// pipe(fd);	Pipes fd[1] as output to fd[0] as input file descriptor (Unidirectional data flow).
// (Process's output written to) fd[1] | ====> (read as INPUT from)fd[0]

// Parent process starts and forks child process, then
// Child writes in fd[1] which is piped to fd[0] via pipe() syscall earlier

// NOTE : Data written to the write end of the pipe is buffered by the  kernel until it is read from
// the read end of the pipe

#include <stdio.h>
#include <unistd.h>

#include "color.h"


int main()
{
	int file_descriptors[2];
	int bytes_read = 0;

	// Create a pipe before forking
	pipe(file_descriptors);			// takes in array[2] of file descriptors as parameter, where 
									// array[0] fd reads input and array[1] file descriptor writes
									// output.

	// fork a child process, which runs concurrently with parent process
	pid_t child = fork();

	// I am the parent and I will read the ouput produced by child process.
	if (child > 0)
	{
		char buffer[100];
		bytes_read = read(file_descriptors[0], buffer, sizeof(buffer));

		// Do anything with the read bytes
		printf(GREEN"[+]"RESET" In parent => Recieved "RED"%d bytes"RESET" : '%s' from child process via pipe \n", bytes_read, buffer);
	}
	
	// I am the child process and my input gets into file descriptor 1 (output fd). Since both the 
	// file descriptors 0 (parent input) and 1(child output) are connected via pipe and data flows
	// from child's output to parent's input, "I am Mahakaal" goes into 
	if (child == 0)
	{
		printf(GREEN"[+]"RESET" In child, producing some output\n");
		write(file_descriptors[1], "I am Mahakaal", 13);
	}

return 0;
}
