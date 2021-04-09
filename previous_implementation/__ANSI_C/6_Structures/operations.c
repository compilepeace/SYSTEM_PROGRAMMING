// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "coordinates.h"
 

int main()
{
	uint32_t choice;

	// menu to user
	printf("Welcome to my program\n");
	printf("1> Area of rectangle\n");
	printf("2> Area of triangle\n");	

	// takes user input
	printf("\nEnter your choice -> ");
	scanf("%u", &choice);
	printf("\n");

	// select desired operation
	switch (choice)
	{
		case 1: init_rectangle();	
				break;

	//	case '2': area_of_triangle();
	//			break;
		
		default : printf("Invalid choice entered! \n");	
				  exit(0x2);
	}
	

return 0;
}


/*void area_of_rectangle(rectangle r1)
{
	uint32_t side1 = 0, side2 = 0, area = 0;

	
	// if same x coordinate, difference between y coordinates
	if (r1.p1.x == r1.p2.x)
		side1 = r1.p1.y - r1.p2.y;

	// if same y coordinate, difference between x coordinates
	else
		side2 = r1.p1.x - r1.p2.x;


	area = side1 * side2;
	
	printf("\nArea of rectangle = %d\n", area);

}
*/

void init_rectangle()
{
	point p1, p2, p3, p4;
	point *ref;
	int counter;
	
	rectangle r1;

	// Take points from user
	for (counter = 1; counter > 0 && counter <= 4; ++counter )
	{
		if (counter == 1)
			ref = &p1;
		else if (counter == 2)
			ref = &p2;
		else if (counter == 3)
			ref = &p3;
		else 
			ref = &p4;
		
		printf("Enter the point%d (space separated) -> ", counter);
	
		scanf("%d %d", &(r1.(ref->x)), &(r1.(ref->y)) );
		//scanf("%d %d", &(ref->x), &(ref->y));
	}
/*
	printf("Enter the coordinates: ");
	scanf("%d %d", &(r1.p1.x), &(r1.p1.y));
	scanf("%d %d", &(r1.p2.x), &(r1.p2.y));
	scanf("%d %d", &(r1.p3.x), &(r1.p3.y));
	scanf("%d %d", &(r1.p4.x), &(r1.p4.y));
	
	area_of_rectangle(r1);
*/
}



