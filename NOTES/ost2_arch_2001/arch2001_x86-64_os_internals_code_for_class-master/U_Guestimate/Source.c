//Guestimate.c: Code to play with RDTSC instruction
//Instructions Learned: RDTSC
//Written by Xeno Kovah, Jan. 12th 2010
//Originally for use with MITRE Institute Intermediate x86 Class
//Licensed under Creative Commons Share Alike license.
//full details available here: http://creativecommons.org/licenses/by-sa/3.0
//P.s. Don't comment on the efficency or style of the code, it's tutorial code! :P

// Updated by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of 
// the Mozilla Public License, v. 2.0

#include <stdio.h>

extern void asm_func();

int main() {
	unsigned long long start, end, diff;

	start = __rdtsc();
	//PUT CODE HERE YOU WANT TO PROFILE

	// Suggestions: moves of immediate -> register vs. reg -> reg vs. mem -> reg, cpuid,
	// the timing of a shift vs multiply, calls with or without frame pointers, etc
	asm_func();

	//END CODE YOU WANT TO PROFILE

	end = __rdtsc();
	diff = end - start;
	printf("Start tick count = 0x%016llx\n", start);
	printf("End tick count = 0x%016llx\n", end);
	printf("The profiled code took 0x%016llx cycles to complete\n", diff);

	return 0xca5cade;
}