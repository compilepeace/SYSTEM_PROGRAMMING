// pthread_join() will join on each thread (i.e. wait for it to finish) and then return to main and
// continue executing main.


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "color.h"

void *myfunc(void *ptr)
{
	printf("In function : %s with %s\n", __FUNCTION__, (char *)ptr);
	return NULL;
}


int main()
{
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, myfunc, "Rudra");
	pthread_create(&tid2, NULL, myfunc, "Kaal");

	void *result;

	pthread_join(tid1, &result);
	printf(GREEN"[-]"RESET" tid1 exited returning result : %s\n", (char *)result);
	pthread_join(tid2, &result);
	printf(GREEN"[-]"RESET" tid2 exited returning result : %s\n", (char *)result);

	int i=0;
	while (i < 3)
	{
		printf(BOLDRED"x_x\n");
		++i;
	}
}
