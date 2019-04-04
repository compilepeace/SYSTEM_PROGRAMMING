
#include <stdio.h>

int main()
{
	long count = 0;	
	int charecter = 0;		// Not of char type since it should be able to store the EOF value, i.e.
							// -1 or 0xffffffff

		while ( (charecter = getchar()) != EOF )
		{
			++count;
			printf("%s: Input charecter = %c\n", __FUNCTION__,  charecter);
		}

	printf("\nThe input consists of %ld number of charecters\n", count);
}
