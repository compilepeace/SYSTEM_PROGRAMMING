
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <time.h>


// time_t time(time_t *t);
// char *ctime( const time_t *timep);


char *CurrentTime()
{
	char *result = malloc(200);
	
		if ( result == NULL ) 
		{
			perror("In CurrentTime");
			exit(1);
		}


	time_t secondsSinceEpoch = time(NULL);
	char *timeASCII = ctime( &secondsSinceEpoch);	

		strcpy(result, timeASCII);
	
	return result;	
}


int main()
{
	char *ptr = CurrentTime();

		printf("%s\n", ptr);
	
		free(ptr);	
		ptr = NULL;				// Just in case we double free it

return 0;
}
