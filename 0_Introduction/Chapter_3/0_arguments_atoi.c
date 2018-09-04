
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{

	int count = 1;
	unsigned long long sum = 0;

		printf("argv[0] : %s\n", argv[0]);
		printf("argc : %d\n", argc);

		for( ; count < argc ; ++count)
		{
			printf("argv[%d] : %s\n", count, *(argv + count));
			sum += atoi( argv[count] );
		}

		printf("Sum  of arguments : %lld\n", sum);		

return 0;
}
