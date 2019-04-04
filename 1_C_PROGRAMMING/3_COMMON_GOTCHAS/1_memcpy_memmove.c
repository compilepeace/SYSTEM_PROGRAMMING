#include <stdio.h>
#include <string.h>
#include <stdlib.h>


int main()
{
	char *destination = (char *)malloc(16);
	char *surname = "Thakur";

	memcpy(destination, surname, 7);

	printf("destination string : %s : %p\n", destination, destination);

	char *name = "Abhinav";
	memmove(destination+7, name, 7);
	
return 0;
}
