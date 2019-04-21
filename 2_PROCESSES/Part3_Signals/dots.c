
#include <unistd.h>
#include <stdio.h>

#define TIME 60


int main()
{
	int i;

	fprintf(stdout, "[+] Process started [PID]: %d\n", getpid());

	for (i = 0; i < TIME; ++i) 
	{
		write(1, ".", 1);
		sleep(1);
	}

return 0;
}
