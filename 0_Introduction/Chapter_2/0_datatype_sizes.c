// C promises to store the numbers between -32,768 to +32,769 (ATLEAST), i.e. an integer will be at
// least 16 bits, 2**16 (16 bit architectures). But the size of an int varies according to architectu// res since C is designed to be suitable and portable for a large number of device architectures 
// from embedded systems to mainframes.


#include <stdio.h>
#include <limits.h>

int main()
{
	int i;
	long int j;
	short int k;
	float f;
	double d; 



	printf("C data types.. int Min & Max for this architecture is : %d to %d\n", INT_MIN, INT_MAX);

	// A Char is not necessarily 1 Byte, But a Char is an 'Addressable Unit' in memory and may vary
	// according to different architectures.
	
	printf("Char size on this machine: %d bits\n", CHAR_BIT);



	printf("Size of int on this architecture is : %d\n", sizeof(i));
	
	printf("Size of short on this arch is : %d\n", sizeof(k));
	
	printf("Size of long on this arch is : %d\n", sizeof(j));
	
	printf("Size of float on this arch is : %d\n", sizeof(f));
	
	printf("Size of double on this arch is : %d\n", sizeof(d));
	
	
	
	
return 0;
}
