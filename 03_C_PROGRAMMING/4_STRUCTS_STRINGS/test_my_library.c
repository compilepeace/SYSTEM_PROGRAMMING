// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com


#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "my_strings.h"

#define STRINGX "my_strncpy function at work"
#define STRINGY "my_strdup function at work"

int main(int argc, char *argv[1])
{
	if (argc != 3)
	{
		printf("Usage: %s <string1> <string2>\n", argv[0]);
		exit(0x10);
	}

    uint8_t *src = argv[1];
    uint8_t *dest = argv[2];


	printf("\n\n=-=-=-=- my_strncmp =-=-=-=-\n\n");
	printf("length of src: %d \nlength of dest: %d\n", my_strlen(src), my_strlen(dest));
	
	if (my_strncmp(src, dest, my_strlen(src)) != 0)
	{
		fprintf(stderr, "%s : %s does'nt match\n", src, dest);
		exit(0x11);
	}
	
	printf("%s : %s matches\n", src, dest);


	printf("\n\n=-=-=-=- my_strncat =-=-=-=-\n\n");

	uint8_t str1[100];
	uint8_t str2[100];
	uint32_t exit_status = 10;
		
	printf("Enter 2 strings \n");
	fscanf(stdin, "%s", str1);
	fscanf(stdin, "%s", str2);

	exit_status = my_strncat(str1, str2, my_strlen(str2));
	
	if (exit_status != 0)
	{
		fprintf(stderr, "Cannot concatenate %s : %s\n", src, dest);
		exit(0x12);
	}

	fprintf(stdout, "Concatenated string : %s\n", str1);

	
	int8_t strncpy_check[100];
	
    printf("\n\n=-=-=-=- my_strncpy =-=-=-=-\n\n");
	
	my_strncpy(strncpy_check, STRINGX, my_strlen(STRINGX));

	printf("After my_strncpy: original string = '%s' : %p\n", STRINGX, STRINGX);
	printf("After my_strncpy: copied string = '%s' : %p\n", strncpy_check, strncpy_check);


    printf("\n\n=-=-=-=- my_strdup =-=-=-=-\n\n");

	uint8_t testit[] = STRINGY;
	uint8_t *ret_strdup;
	
	printf("Address of string supplied to strdup : %s <--- %p\n", testit, testit);	
	
	ret_strdup = my_strdup(testit);

	printf("String strdup returned: %s <--- %p\n\n",ret_strdup, ret_strdup); 

    printf("\n\n=-=-=-=- END =-=-=-=-\n\n");

}

