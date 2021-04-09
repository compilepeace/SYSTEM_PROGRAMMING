
#include <stdio.h>
#include <stdint.h>

#define MAXLEN 1000


uint32_t GetLine(uint8_t line[], uint32_t maxlen);
void copy(uint8_t to[], uint8_t from[]);
void print_array(uint8_t arr[], uint32_t );


uint32_t main()
{
	uint32_t length = 0, maxlength = 1;
	uint8_t user_line[MAXLEN] = {};
	uint8_t longest[MAXLEN] = {};
	

		while ( length = GetLine(user_line, MAXLEN) )
		{
			if (length > maxlength)
			{
				copy(longest, user_line);					// save the line
				maxlength = length;
			}	
		}

	printf("The longest line is - \n");
	print_array(longest, maxlength);

return 0;
}


// gets a line from user until EOF is reached or user enters no charecter after '\n'
uint32_t GetLine(uint8_t line[], uint32_t lim)
{
	uint32_t character = 0, i=0, len=0;

		while ((character = getchar()) != EOF & i < lim-1)
		{
			if (character == '\n')
			{
				line[i] = '\0';
				break;
			}

			line[i] = character;
			++len;
			++i;
		}

	printf("Returning length: %d\n", len);
	return len;
}


// copies one array into another
void copy(uint8_t to[], uint8_t from[])
{
	uint32_t i=0;

		while ( (to[i] = from[i]) != '\0')
			++i;	
}


// Prints an array
void print_array(uint8_t arr[], uint32_t len)
{
	uint32_t i;

		for (i=0 ; i < len ; ++i)
			printf("%c", arr[i]);
	
	printf("\n");
}

