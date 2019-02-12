

#include <stdio.h>

int main()
{
	
	char *pointer = "This is a string literal, i.e. an immutable string and is stored in code segment of memory";

	char array[] = "This string is mutable";

	
	// 2 same string literals, both of them reside in same memory location
	char *str1 = "hello";
	char *str2 = "hello";

	printf("Pointers string literals at : %p and %p\n", str1, str2);
	
	// Arrays contain deep copies of string literals
	char arr1[] = "yo";
	char arr2[] = "yo";

	printf("Arrays store deep copies at : %p and %p\n", arr1, arr2);



return 0;
}
