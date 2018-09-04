
#include <stdio.h>


int main()
{
	char *ptr = "Hello Critical";
	char array[] = "Hello Critical";

	// Size of a pointer variable depends on the architecture, i.e. on a 32 bit machine
	// it will store a 32 bit address, therefore it has a size of 4 bytes.
	// whereas on a 64 bit machine, it will take 8 bytes in RAM to store a 64 bit address. 
	printf("Sizeof(ptr) : %ld bytes \nSizeof(array): %ld bytes\n", sizeof(ptr), sizeof(array));


	//	The pointer is pointing to a string constant and therefore can only be derefferenced and 
	//	cannot be modified whereas arrays are modifiable. 
	//	*(ptr + 1) = '*';				// Error!!
		*(array + 1) = '*';
		
	printf("ptr: %s \narray: %s\n", ptr, array );
	

return 0;
}
