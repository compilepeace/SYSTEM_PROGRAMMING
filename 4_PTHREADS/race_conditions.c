
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define MAX_THREADS 10


struct T
{
	pthread_t id;
	int value;
	char result[50];
};


void *myfunc(void *ptr)
{
	int n =  (int )(((struct T *)ptr)->value) ;

	printf("%d ", n);

	return NULL;
}


int main()
{
	int i;
	
	// An array of 10 objects of type strcut T (initialized to 0)
	struct T *t_info = calloc(10, sizeof(struct T));


	for (i = 0; i < MAX_THREADS; ++i)
	{
		t_info[i].value = i;
		pthread_create(&(t_info[i].id), NULL, myfunc, &t_info[i]);
	}
	pthread_exit(NULL);

return 0;
}
