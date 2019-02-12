
#include <stdio.h>

// long int strtol(const char *nptr, char **endptr, int base);

// long long int strtoll(const char *nptr, char **endptr, int base);



int main()
{
	const char *number_string = "12a";
	char *endptr;

	long int result = strtol(number_string, &endptr, 16);
	
	printf("%d\n", result);

return 0;
}
