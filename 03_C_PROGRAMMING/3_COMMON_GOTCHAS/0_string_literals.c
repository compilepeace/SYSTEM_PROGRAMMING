// To have a look where the string is stored in the binary -
// $ readelf -S ./binary_name							# Shows you all the sections numbers
// $ readelf -p section_number_of_rodata ./binary_name	# Shows all strings in that section

#include <stdio.h>
#include <string.h>


int main()
{
	
	char *pointer = "This is a string literal, i.e. an immutable string and is stored in .rodata section and code segment of memory";

	char array[] = "This string is mutable";

	
	// 2 same string literals, both of them reside in same memory location
	char *str1 = "hello";
	char *str2 = "hello";

	printf("Pointers string literals at : %p and %p\n", str1, str2);
	
	// Arrays contain deep copies of string literals
	char arr1[] = "yo";
	char arr2[] = "yo";

	printf("Arrays store deep copies at : %p and %p\n", arr1, arr2);


	// Finds the string (2nd argument) in the string pointed to by 1st argument and returns a pointer
	// to the found string.
	char *find = "code";
	char *string_found = strstr(pointer, find);
	if (string_found != NULL)
		printf("String : %s ----- found at: %p\n", string_found, string_found);
	else
		printf("Cannot find %s\n", find);

	//
	char *needle = "a";
	char *test_string = "This is a 9 and is up-side-down 6";
	char *needle_found = strstr(test_string, needle);
	if (needle_found != NULL)
		printf("Needle : %s ----- found at : %p\n", needle_found, needle_found);
	else
		printf("Cannot find needle: %s\n", needle);


return 0;
}
