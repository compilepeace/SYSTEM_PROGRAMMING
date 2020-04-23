// Can I make child process execute another program ??

// Use one of the exec() family of functions after forking. The 'exec' set of functions replaces the
// process image with the process image of what is being called. This means that any lines of code
// after exec are replaced. Any work you want the child to do should be done before exec call.


/*

The base of each is exec (execute), followed by one or more letters:

   e – An array of pointers to environment variables is explicitly passed to the new process image.

   l – Command-line arguments are passed individually (a list) to the function.

   p – Uses the PATH environment variable to find the file named in the file argument to be executed.

   v – Command-line arguments are passed to the function as an array (vector) of pointers.
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t child = fork();

	if (child == -1) exit(0x10);

	// Parent
	if (child > 0)
	{
		int status;
		waitpid(child, &status, 0);
		exit(0);
	}

	// Child
	else
	{
		// First arg is name of the program to be executed
		// Last argument must always be a pointer to NULL
		execl("/usr/bin/find", "find", ".", "-type", "f", "-name", "*.c", (char *)NULL);

		// If this line executes, something went wrong with execl()
		perror("execl failed!\n");
	}


return 0;
}
