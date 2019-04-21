// The child process can find its parent (the original process that was duplicated) by using
// 'getppid()' (therefore does not need any return information from fork()). But the parent process
// can only find the id of new child process from return value of fork().


#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t id = fork();

	if (id < 0)
	{
		printf("Fork failed\n");
		exit(0x10);
	} 

	// if parent process
	else if (id > 0)
	{	
		// use waitpid to wait for the child to finish
		printf("Hell that, I am the parent process's block\n");
	}

	// if child process
	else if (id == 0)
	{
		// executed by child process
		printf("Yasss, and I am the child process's block\n");
	}

}
