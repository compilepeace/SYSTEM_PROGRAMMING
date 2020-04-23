// It is very dangerous to return pointer to a function's local members...
// Because as soon as the function returns, the local members no longer exist on stack
// and therefore the pointers then point to unapointed locations.



#include <stdio.h>
#include <stdlib.h>



// Recurssion 
void f1(int x)
{
	char array[10] = {};
			
		printf("%s => Array is at: %p\n", __FUNCTION__, array); 
		
		if (x > 0) f1(x - 1);
}

int main()
{
	f1(10);

return 0;
}


