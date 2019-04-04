
#include <stdio.h>
#include <stdint.h>


int main()
{
	uint32_t counter = 0; 
	uint32_t c=0;			// Not of char type (8 bits) since it should be able to store a 32-bit
							// value of EOF i.e. -1 or 0xffffffff

		while ( (c = getchar()) != EOF )
		{
			if (c == '\n')
				++counter;
		}

	printf("User input contains %d lines\n", counter);
}
