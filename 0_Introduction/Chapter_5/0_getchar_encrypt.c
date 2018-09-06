
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	int c;

		while( (c = getchar()) != EOF)
		{
			// Encrypt (flip the lowest bit) of all printable charecters
			if ( c > 32 )
				c = c ^ 1;
			putchar(c);
		}
	
	puts("done");

return 0;
}
