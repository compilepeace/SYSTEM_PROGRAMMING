
#include <stdio.h>
#include <stdint.h>

#define MAXCHAR


uint32_t GetLine();
void print_array(uint8_t arr[], uint32_t len);



int main()
{
	uint32_t flag = 0;

	while (flag == 0)
		flag = GetLine();
			

return 0;
}


uint32_t GetLine()
{
	uint32_t character=0, i=0, count = 0, flag = 0;
	uint8_t arr[1000];

	printf("Enter the line of input: ");	
	flag = 1;
	
		while ((character = getchar()) != EOF)
        {
            if (character == '\n')
            {
				arr[i] = '\0';
    			flag = 0;
				break;
			}	
            arr[i] = character;
			++count;
			++i;
        }

	if (count > 80)
		print_array(arr, count);


	return flag;
}

void print_array(uint8_t x[], uint32_t len)
{
	uint32_t i=0;

		while (i < len)
		{
			printf("%c", x[i]);
			++i;
		}
	printf("\n");
}
