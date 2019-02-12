// The header files generally contain the function declarations and symbol definitions (macros).
// When we include the header files in our source code, it replaces the '#include' with the contents
// of header file.
// You can have a look at what is stored in 'stdio.h' by using cat command -
// 'cat /usr/include/stdio.h'


// POINTER ARITHEMETIC
// Pointer Arithemetic is always scaled in C programming language by the sizeof(type) that the
// pointer is pointing to, pointer arithemetic can't be performed on void pointers.
// For eg:
// ++pointer;		// This statement can't execute until the compiler knows the type of 'pointer'



#include <stdio.h>

int main()
{
	char *pointer = "Abhinav";	
	int *int_ptr = (int *)pointer;

		int_ptr += 1;

	printf("%s\n", int_ptr);

return 0;
}


