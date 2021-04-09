#include <stdio.h>
#include <stdint.h>


int32_t power(int, int);


int32_t main()
{
	int32_t i=0;

		for (i=0; i<10; ++i)
			printf("i: %d, pow 2: %d, pow 3: %d\n", i, power(2,i), power(-3, i)); 	

return 0;
}


int32_t power(int base, int n)
{
	int32_t result = 1;
	
	for(int i=0; i < n; ++i)
		result = result * base;

	return result;
}
