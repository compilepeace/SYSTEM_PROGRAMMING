// You can still use CTRL+\ to Abort program


#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

// sighandler_t signal(int signum, sighandler_t handler);




void KeyboardInterruptHandler(int signal)
{
	//write(STDOUT_FILENO, " HAHA ^_~\n", 10);
	printf(" HAHA ^_~ signal : %d\n", signal);
}


void AlarmHandler(int signal)
{
	printf("Alarm !!!! : %d\n", signal);
}



int main()
{
	char *ptr = getenv("SHELL");

	alarm(5);
	
	// 2nd argument is a function pointer
	signal(SIGINT, KeyboardInterruptHandler);

	signal(SIGALRM, AlarmHandler);	

	while(1)
	{
		puts(ptr);
		sleep(2);	
	}

return 0;
}
