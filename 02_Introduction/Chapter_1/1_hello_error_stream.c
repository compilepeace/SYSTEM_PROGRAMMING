
#include <unistd.h>

#define STDOUT_FILENO 1 
#define STDERR_FILENO 2

int main()
{
	int count;
		
		for (count = 0; count < 10 ; ++count)
		{
			write(STDOUT_FILENO, "Legit\n", 6);
			write(STDERR_FILENO, "*\n", 2);
		}

return 109;
}
