#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "color.h"

int main()
{
	char *ptr = (char *)malloc(500);
	int i;


	fprintf(stdout, GREEN"[+]"RESET" Newly allocated buffer @"RED" %p : %s\n", ptr, ptr);
	strcpy(ptr, "0xDeadbeef" );
	fprintf(stdout, GREEN"[+]"RESET" Closing ptr.. : %s\n", ptr);

	for (i = 0; i < 500; ++i)	
		printf(BOLDMAGENTA"%d ", *(ptr + i));

	free(ptr);

	char *ptr2 = (char *)malloc(500);

	for (i = 0; i < 500; ++i)
		printf(BOLDYELLOW"%d ", *(ptr2 + i));

	fprintf(stdout, GREEN"\n[+]"RESET" Again allocating buffer @" RED" %p: %s\n", ptr2, ptr2); 


return 0;
}
