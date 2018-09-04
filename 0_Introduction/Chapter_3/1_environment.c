
#include <stdio.h>
#include <stdlib.h>

#define ENV_VAR "PATH"

// extern means that give me access to the 'environ' variable declared somewhere
// We don't want to allocate storage for this variable but the storage for this var
// has already been made somewhere, and we just want to use it.
extern char **environ;

int main(int argc, char **argv)
{
	if (argc < 2)
	{
		printf("%s <env_var>\n", argv[0]);
		exit(1);
	}

	char *value = getenv(argv[1]);

 	printf("%s : %s\n", argv[1], value);


/*
	// code to view all environment variables with the help of an extern variable called 'environ'
	printf("-=-=-=- OUR ENVIRONMENT -=-=-=-\n\n");
	char **ptr = environ;
	
		while ( *ptr )
		{
			printf("%s\n", *ptr);
			++ptr; 
		}
*/

return 0;
}
