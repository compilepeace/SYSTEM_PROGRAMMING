
#include <stdio.h>
#include <stdint.h>


#define NO 0
#define YES 1

int main()
{
	uint32_t new_line, new_char, new_word, previously_found;
	uint32_t charecter = 0;	

	new_line = new_char = new_word = 0;
	previously_found = NO;


		// Take charecter by charecter input from user
		while ((charecter = getchar()) != EOF)
		{
			new_char++;

			// count newline
			if (charecter == '\n')
				new_line++;
			

			// count word only if previously not found
			if ( (charecter == ' ' || charecter == '\n' || charecter == '\t') && (previously_found == NO) )
            {
				new_word++;
				previously_found = YES;
			}			

			else if (charecter != ' ' && charecter != '\n' && charecter != '\t')
				previously_found = NO;
			
		}

	printf("%d\t%d\t%d\n", new_line, new_word, new_char);

return 0;
} 
