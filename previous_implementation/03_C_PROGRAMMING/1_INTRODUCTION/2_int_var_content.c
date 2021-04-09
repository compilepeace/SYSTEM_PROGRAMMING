
#include <stdio.h>

#define VALUE 128


// Till value 127, the output is first byte: 127 (2**7 - 1) and other bytes 0.
// But as soon as the value exceeds 127(2**7 - 1) and is 128 (2**7), the first bit (most significant
// one) of the 'int_var' becomes 1, i.e the sign bit, Therefore, the output comes out to be
// First byte: -128, and all bytes 0.




int main()
{
	unsigned int int_var = VALUE;
	char *ptr = &int_var;
		

	printf("Bellow is the content of integer variable (which is 4 bytes) in memory\n");


	printf("First byte:  %d\n", *ptr);
	printf("Second byte: %d\n", *(ptr + 1));
	printf("Third byte:  %d\n", *(ptr + 2));
	printf("Fourth byte: %d\n", *(ptr + 3));


return 0;
}
