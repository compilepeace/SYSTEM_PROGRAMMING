// Put whatever code you want to test here

extern unsigned char* asm_scratchpad();

#include <stdio.h>

void main()
{
	unsigned char* rip = 0;
	rip = asm_scratchpad();
	printf("byte @ rip (0x%016x) = 0x%02x", rip, *rip);
}