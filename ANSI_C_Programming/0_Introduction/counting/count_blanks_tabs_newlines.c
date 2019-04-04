
#include <stdio.h>
#include <stdint.h>

int main()
{
	uint32_t blanks = 0, tabs = 0, newlines = 0, charecter;

		while ((charecter = getchar()) != EOF)
		{
			switch(charecter)
			{
				case '\n':  ++newlines;
							break;
				case '\t': 	++tabs;
							break;
				case ' ': 	++blanks;
							break;
			}
		}

	printf("\n\nUser input contains \nnewlines: %d \ntabs: %d \nblanks: %d\n", newlines, tabs, blanks);

return 0;
}
