
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main()
{
	pid_t id;

	while (1)
	{
		id = fork();
		
		if (id == -1)
		{
			perror("Forked failed\n");
			exit(0x10);
		}

		if (id == 0)
			printf("I'm the child\n");
		
		if (id > 0)
			printf("I'm the parent with pid: %d\n", id);
	}
return 0;
}
