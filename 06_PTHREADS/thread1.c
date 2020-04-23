// Here, the 2 threads will probably not have time to get started. Therefore we need to have some 
// functionality to wait for the threads to finish. That's where 'pthread_exit' and 'pthread_join'
// comes to our rescue.

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>


void *myfunc(void *ptr)
{
	printf("In %s\n", __FUNCTION__);
	return NULL;
}


int main()
{
	pthread_t tid1, tid2;

	pthread_create(&tid1, NULL, myfunc, "Abhi");
	pthread_create(&tid2, NULL, myfunc, "Thakur");

	exit(0x10);
}
