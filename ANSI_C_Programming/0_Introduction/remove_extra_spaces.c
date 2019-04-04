
#include <stdio.h>
#include <stdint.h>

int main()
{
	uint32_t charecter = 0, space_found = 0;

		while ((charecter = getchar()) != EOF) 
		{
			// If no blankspace is found previously
			if (charecter == ' ' && space_found == 0 )
			{
				printf("%c", charecter);
				space_found = 1;		// we got a space
			}	

	
			// If the previous charecter was a blankspace
			else if (charecter == ' ' && space_found != 0)
				continue;				// run the loop again, take another charecter


			// If any charecter other than blankspace is found
			else 
			{
				printf("%c", charecter);
				space_found = 0;	
			}
		}

return 0;
}
