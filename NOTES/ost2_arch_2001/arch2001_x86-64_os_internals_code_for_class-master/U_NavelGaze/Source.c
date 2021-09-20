// NavelGaze.c: Showing how setting a breakpoint in code can influence its behavior if it's self-aware
// Written by Xeno Kovah, Jan. 12th 2010
// Originally for use with MITRE Institute Intermediate x86 Class
// Licensed under Creative Commons Share Alike license.
// full details available here: http://creativecommons.org/licenses/by-sa/3.0
// P.s. Don't comment on the efficency or style of the code, it's tutorial code! :P

// Modified by Xeno Kovah in 2021 for OpenSecurityTraining2 Architecture 2001 class
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0

#include <stdio.h>

// prototypes
void someFunction1();
int someFunction2();
void someFunction3();
void someMaliciousFunction();
void someBenignFunction();

// Globals used for timing checks, but set in various places
unsigned long long gStart, gEnd, gDiff;

int main() {

	someFunction1();
	//		For lab purposes, run this first with a breakpoint at someFunction2()
	//		and just continue and see the result. Then run without the breakpoint
	//		and see the result.
	someFunction2();
	someFunction3();
	if (gDiff < 0x800000) {
		someMaliciousFunction();
	}
	else {
		someBenignFunction();
	}

	return 0x7ac71e55;
}

// "Secretly" aquires a start time
void someFunction1() {
	// Assume the following code is mixed in with a bunch of other code
	gStart = __rdtsc();
}

// This is the function to time, which the attacker knows an analyst might put a breakpoint in
int someFunction2() {
	//Assume the following code is mixed in with a bunch of other code
	return 0xa1fa1fa;
}

// "Secretly" aquires an end time
void someFunction3() {
	//Assume the following code is mixed in with a bunch of other code
	gEnd = __rdtsc();

	gDiff = gEnd - gStart;
}


void someMaliciousFunction() {
	printf("La de da de da, got yo @$$ haxed didn't ya?\n");
}

void someBenignFunction() {
	printf("La de da de de, I'm as innocent as can be!\n");
}