// Example taken from https://github.com/angrave/SystemProgramming/wiki/Synchronization%2C-Part-1%3A-Mutex-Locks#simplest-complete-example


#include <stdio.h>
#include <pthread.h>

#include "color.h"


pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;

int sum = 0;


void *countgold(void *param)
{
	int i;

	printf(GREEN"\n[+]"RESET" In"YELLOW" %s"RESET", Trying to lock mutex 'm'...\n", (char *)param );

	// Same thread that locks the mutex (the lock) must unlock it.
	// The thread executing will try to lock this mutex type variable 'm'
	// Now other threads which call this function to lock the variable 'm' will have to wait until
	// we call unlock and release the resource (the variable 'm')
	pthread_mutex_lock(&m);

	printf(YELLOW"%s"RESET" locked mutex m\n",(char *)param); 
	printf("In critical section of "RED"%s ^_^\n", (char *)param);

	for (i = 0; i < 1000000; ++i)			//
	{										//  This is the 
		sum += 1;							//	Critical Section 
	}										//

    printf(GREEN"[+]"RESET" In "YELLOW"%s"RESET", Now unlocking mutex 'm'...\n\n", (char *)param );
	
	pthread_mutex_unlock(&m);


	return NULL;
}

int main()
{
	pthread_t tid1, tid2;

  	printf(GREEN"\n\n=-=-=-=-=-=-   MUTEX    -=-=-=-=-=-=\n\n\n");

	
	pthread_create(&tid1, NULL, countgold, "Thread 1");
	pthread_create(&tid2, NULL, countgold, "Thread 2");

	// Wait for both threads to finish
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	fprintf(stderr, "\n[+]With Mutex/lock Sum is %d\n", sum);
	printf("\n\n\n");

return 0;
}
