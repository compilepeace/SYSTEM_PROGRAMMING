
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

// sig_atomic_t Ensures that all the bits of the var can be read/modified as an 'Atomic Operation
sig_atomic_t stopnow;


void my_signal_handler()
{
	stopnow = 1;
}

int main()
{
	int i = 0;
	signal(SIGINT, my_signal_handler);
	
	stopnow = 0;

	while (! stopnow)
	{
		while (i--)
		{
			write(1, "^_^ ", 4);
			sleep(1);
		}
	}

	
}
