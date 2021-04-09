// NOTE: EOF charecter is Ctrl+d on linux platform and Ctrl+z on windows platform


#include <stdio.h>

main()
{
	int c;

	// getchar() takes a charecter as input from the keyboard and returns the charecter
	// which is then stored in variable 'c'
	while ( (c = getchar()) != EOF)
	{
		printf("%s: EOF = %d, ", __FUNCTION__, EOF);
		putchar(c);
		printf("\n");
	}
}
