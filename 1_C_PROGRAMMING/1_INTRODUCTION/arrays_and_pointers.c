
// Difference between arrays and pointers
// Arrays are doomed to point to memory on stack only whereas pointers can point to other memory 
// segments(heap) also. And Pointers cannot alter the string it points to whereas arrays are mutable.


#include <stdio.h>


int main()
{
	char *ptr = "A fixed String";
	char array[] = "A mutable array";


		

return 0;
}
