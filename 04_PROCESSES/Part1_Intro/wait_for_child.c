// How does parent process waits for child to finish ??

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	pid_t id = fork();

		
	printf("fork returned : %d\n", id);
	
		if (id == -1)
		{
			perror("fork");
			exit(0x10);
		}

		// If parent process
		else if (id > 0)
		{
			int status = 0x10;
			pid_t return_id = 0x10;

			return_id = waitpid(id, &status, 0);
			printf("In parent block..\n");
			printf("\tReturn_id from waitpid(): %d\tstatus variable: %d\n", return_id, status);
		}

		// If child process
		else
		{
			fprintf(stderr, "In child block... exiting\n");
			exit(0x11);
		}	

return 0;
}
