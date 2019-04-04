#include <stdio.h>
#include <math.h>

int main()
{
	char c;
	int i;
	double d;
	float f;
	unsigned int ui;
	unsigned char uc;
	short int si;
	long int li;
	long double ld;
	

		// The ranges can be calculated by - 2 raise to the power n.
		// where n is the no. of bits in the type's size.

		printf("Basic Types Sizes -\n");
		printf("char = %ld Bytes, Range = %.0f\n", sizeof(c), pow(2, sizeof(c)*8));
		printf("int  = %ld Bytes, Range = %.0f\n", sizeof(i), pow(2, sizeof(i)*8));
		printf("double = %ld Bytes, Range = %.0f\n", sizeof(d), pow(2, sizeof(d)*8));
		printf("float = %ld Bytes, Range = %.0f \n", sizeof(f), pow(2, sizeof(f)*8));
		
		printf("\nExtended types - \n");
		printf("unsigned int = %ld bytes, Range = %.0f\n", sizeof(ui), pow(2, sizeof(ui)*8));
		printf("unsigned char = %ld bytes, Range = %.0f\n", sizeof(uc), pow(2, sizeof(uc)*8));
		printf("short int = %ld bytes, Range = %.0f\n", sizeof(si), pow(2, sizeof(si)*8));
		printf("long int = %ld bytes, Range = %.0f\n", sizeof(li), pow(2, sizeof(li)*8));
		printf("long double = %ld bytes, Range = %.0f\n", sizeof(ld), pow(2, sizeof(ld)*8));	

return 0;
}		
