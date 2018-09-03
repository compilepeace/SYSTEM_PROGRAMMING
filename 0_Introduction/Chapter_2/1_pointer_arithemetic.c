
#include <stdio.h>

#define FIRST_ENTRY 0
#define LAST_ENTRY 9

void print_array(int *, int);
void swap_entry(int *, int, int);


int main()
{
	int array[10];

	printf("Array is at address: %p \n", array);
	printf("Array + 1 is at address: %p \n", array + 1);
	printf("Array + 2 is at address: %p \n", array + 2);

		print_array(array, 10);

	*(array) = 10;
	*(array + 1) = 11;
	*(array + 2) = 12;
	*(array + 3) = 13;

		print_array(array, 10);

	array[1] = 90;
	2[array] = 92; 			// This is a secret ^_~

		print_array(array, 10);

		swap_entry(array, FIRST_ENTRY, LAST_ENTRY);

		printf("Now.. the last entry is swapped\n");
		print_array(array, 10);	

return 0;
}


void print_array(int *array, int n)
{
	int i;
	
	printf("Array : ");
	
		for( i=0 ; i<n ; ++i)
			printf("%d ",  *(array + i));

	printf("\n");
}


void swap_entry(int *a, int pos1, int pos2)
{
	int temp=0;

		temp = *(a + LAST_ENTRY);
		*(a + LAST_ENTRY) = *(a + FIRST_ENTRY);
		*(a + FIRST_ENTRY) = temp;	
}			
