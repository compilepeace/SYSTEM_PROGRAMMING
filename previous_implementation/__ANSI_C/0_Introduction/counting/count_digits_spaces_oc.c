
#include <stdio.h>
#include <stdint.h>

int main()
{
	uint32_t space, oc, array[10] = {};
	uint32_t character = 0;

	space = oc = 0;

		while ((character = getchar()) != EOF)
		{
			if (character == ' ' || character == '\n' || character == '\t')
				space++;

			else if (character >= '0' && character <= '9')
				array[character - '0']++;			// Subtract ASCII code of '0' from every number
											// to increment the corresponding subscript of 
											// character encountered
				
			else
				oc++;
		}	

	
	for (int i=0; i < 10 ; ++i)
		printf("%d ", array[i]);

	printf(", white space = %d, other characters = %d\n", space, oc);

return 0;
}
