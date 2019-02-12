
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>


// char *fgets(char *s, int size, FILE *stream);
// ssize_t getline(char **lineptr, size_t *n, FILE *stream);


#define BUFFER_SIZE 1024

int main()
{
	char buffer[10];
	char *buffer2 = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	
		if (buffer2 == NULL)
		{
			printf("malloc: Unable to allocate memory\n");
			exit(-1);
		}	


	ssize_t size = 10;



	
	char *return_val;

	
	printf("Please enter something: ");

		// fgets() copies the newline also into the buffer
		return_val = fgets(buffer, sizeof(buffer), stdin);
	
		if (return_val == 0)
		{
			perror("fgets() failed to take value as input \n");
			exit(-1);
		}




	printf("Getline() in action..\n");
	printf("getline() is asking for line of input : ");
		// getline() will automatically re-allocate buffer on heap
		getline( &buffer2, &size, stdin);		


	printf("Buffer2: %s", buffer2);
	printf("Return value of fgets: %s", return_val);
	printf("fgets threw value in buffer: %s\n", buffer);

	free(buffer2);
}
