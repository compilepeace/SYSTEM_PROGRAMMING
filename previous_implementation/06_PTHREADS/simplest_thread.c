

#include <stdio.h>
#include <pthread.h>


// int pthread_create(pthread_t *thread, const pthread_attr_t *attr,
//                          void *(*start_routine) (void *), void *arg);
void *busy(void *ptr)
{
	puts("Hello Hell \n");
	return NULL;
}


int main()
{
	pthread_t thread_id;

	pthread_create(&thread_id, NULL, busy, "Abhi");


	// go on an endless loop
	while(1) {} 

return 0;
}
