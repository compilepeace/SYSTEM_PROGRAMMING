// fork(): parent ko return krta hai ek positive intger (i.e. child process's PID).
// fork(): Child ko return krta hai 0.

// Both the processes created by fork() are running concurrently.
// 1st fork() - (Parent) + (Child1) processes are created
// 2nd fork() - (Parent + Child2) + (Child1 + Child3)
// 3rd fork() - (Parent + Child4) + (Child2 + child5) + (Child1 + child6) + (Child3 + child7)
// ..
// fork() --- called 'n' times => 2**n processes will be created


#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
	pid_t id = 0;

	printf("[+] Program started with [PID] -> %d\n", (int )getpid());


	id = fork();

	printf("[+] Fork returned %d\n", (int )id);

	if (id < 0)	perror("Fork");

	// 0 is returned in the child
	else if (id == 0)
	{
		printf("[*] In child: PID of child -> %d\n", (int )getpid());	
		printf("-> Sleeping for 5 seconds...\n");
		sleep(5);
		printf("-> Child exiting...\n");
		exit(0x10);
	}

	// The PID of child is returned in parent
    else if (id > 0)
    {
        printf("[*] In parent: PID of child -> %d\n", (int )id);
    }


return 0;
}
