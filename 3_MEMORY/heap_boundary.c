// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com



#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include "color.h"


int main(int argc, char *argv[])
{
	uint32_t i, n, bytes = 1024;

	// default value of 'n' in 2
	if (argc < 2)
		n = 2;
	else
		n = atoi(argv[1]);

	
	fprintf(stdout, "Initially the heap ends at (program break):"RED" %p \n\n", sbrk(0));

	for (i = 0; i < n ; ++i)
	{
		fprintf(stdout, GREEN"[+]" RESET" Allocating %d bytes \n", bytes);
		malloc(bytes);
		
		fprintf(stdout, "\t-> (program break) Heap ends at" RED" %p \n", sbrk(0));
	}


return 0x0;
}
