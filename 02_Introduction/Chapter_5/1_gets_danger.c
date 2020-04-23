#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
	int number = 0x10203040;
	char buffer[12];

	printf("number : %x\n", number);
	gets(buffer);			// Input greater than 12 bytes will corrupt the 'number' variable
	
	printf("number : %x\n", number);

return 0;
}
