// Each forked process will have its own address space and its own set of variables


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	
	printf("Now started\n");		
	
		while(1)
		{
			fork();
			printf("forkid : %d\n", getpid());
			sleep(2);
		}

return 0;
}
