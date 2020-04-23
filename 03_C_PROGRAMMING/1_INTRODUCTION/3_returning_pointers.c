
#include <stdio.h>

char *function()
{
	char *ptr = "Hello";
	
	return ptr;
}



// Since array here is not located in the stack segment and rather has static storage allcoation, 
// i.e. in '.data' or '.bss' segment, therefore the strings "Critical" in array[] persists even
// after stack frame of 'function3' is removed from stack segment.
char *function3()
{
	static char array[] = "Critical";
	
	return array;
}


// This function will cause a SIGSEGV - segmentation fault
// Since the space for array[] is allocated on the stack segment on the stack frame of 'function2', 
// which is removed from stack segment after function2() is finished doing its work. Therefore, 
// array[] becomes invalid after the 'function2()' returns;
char *function2()
{
	char array[] = "World";

	return array;
}


int main()
{
	printf("%s\n", function());
	printf("%s\n", function3());
	printf("%s\n", function2());

return 0;
}
