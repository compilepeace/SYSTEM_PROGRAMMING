// sscanf() returns how many parameters it has correctly parsed


#include <stdio.h>
#include <stdlib.h>

int main()
{
	char *data = "Abhinav 1000";

	char name[20];
	int marks = 0;
		
	int parameters_parsed = sscanf(data, "%s %d", name, &marks);

    printf("Result : %s : %d : %d\n", name, marks, parameters_parsed);


	fscanf(stdin, "%s %d", name, &marks); 		// We can pass file stream in here


	printf("Result : %s : %d : %d\n", name, marks, parameters_parsed);
	

return EXIT_SUCCESS;
}
