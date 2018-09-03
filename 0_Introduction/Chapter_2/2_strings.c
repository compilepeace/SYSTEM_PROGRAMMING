
#include <stdio.h>
#include <string.h>


void ascii_to_integer(char *);
void string_reverse(char *);


int main()
{
	char *ptr = "A simple string";

	ascii_to_integer(ptr);

	string_reverse(ptr);

	printf("\n");	

return 0;
}


void ascii_to_integer(char *str)
{
	printf("ASCII  INTEGER\n");

	while( *str )
	{
		printf("%c      %d\n",*str, *str );
		++str;
	}

	printf("\n");
}


void string_reverse(char *str)
{
	char *ptr = (str + strlen(str) - 1);
	
	printf("Length of entered string is : %d\n", strlen(str));

	printf("String in reverse is : ");
	
		while (ptr != str - 1)
		{	
			printf("%c", *ptr);
			--ptr;
		}

}
