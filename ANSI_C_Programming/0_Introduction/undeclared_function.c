
#include <stdio.h>
#include <stdint.h>


int main()
{
	uint32_t ret_value = 119;

		ret_value = yas();

	printf("function yas returned : %d\n", ret_value);
	
return 0;
}

yas()
{
	printf("in function %s\n", __FUNCTION__);
}
