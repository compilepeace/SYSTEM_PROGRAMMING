#include <stdio.h>
#include <stdint.h>


int main()
{
	uint32_t character;

		while ( (character = getchar()) != EOF)
		{
			// check for tabspace
			if (character == '\t')
				printf("\\t");

			// check for backspace
			else if (character == '\b')
				printf("\\b");		

			// check for backslash
			else if (character == '\\')
				printf("\\");
			
			else 
				printf("%c", character);

		}
	

return 0;
}
