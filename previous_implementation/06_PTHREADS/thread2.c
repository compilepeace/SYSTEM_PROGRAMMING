// Process will continue to exist until both of the threads have finished
// pthread_exit terminates the parent process too.

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "color.h"


void *myfunc(void *ptr)
{
	printf("In function %s with parameter : %s\n", __FUNCTION__, (char *)ptr);
	return NULL;
}


int main()
{
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, myfunc, "Jack");
	pthread_create(&tid2, NULL, myfunc, "Daniels");

	pthread_exit(NULL);

	int i=0;

	while (i < 3)
	{
		printf(BOLDRED"x_x\n");
		++i;
	}
}
