
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


//pid_t waitpid(pid_t pid, int *wstatus, int options);



int main()
{
	printf("Hello all\n");

	pid_t child_pid = fork();

		// If fork returns a positive value for child_id then I'm (the process) the parent
		if ( child_pid > 0 )
		{	
			int status;
			waitpid(child_pid, &status, 0);
			printf("I', the parent: %d\n", getpid());		
		}

		// fork returns a 0 value for child_id means I'm (the process) the child
		if ( child_pid == 0 )
			printf("I'm the mischevious child: %d\n", getpid());
	

	printf("Yeah: %d\n", getpid());
}
