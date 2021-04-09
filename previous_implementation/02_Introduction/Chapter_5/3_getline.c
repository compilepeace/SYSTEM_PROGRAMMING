
// To get the declaration of getline included (This is done with older compilers as old POSIX 
// standards
// Getline() uses heap to allocate memory automatically

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>


// ssize_t : signed size variable
// ssize_t getline(char **lineptr, size_t *n, FILE *stream);


int main()
{
	char *buffer = NULL;
	size_t capacity = 0;


	ssize_t length = getline( &buffer, &capacity, stdin);

	if (length > 0 && buffer[length - 1] == '\n')
		buffer[length - 1] = 0;
	
	

	printf("%d : %s", length, buffer);
	


return EXIT_SUCCESS;
}

