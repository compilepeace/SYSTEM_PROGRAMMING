// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Decription : This program uses semaphores as mutexes by initializing semaphore with a value of
//				1 and using "sem_wait" in place of "pthread_mutex_lock" and "sem_post" in place
//				of "pthread_mutex_unlock".


#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#include "color.h"


sem_t lock;

int sum = 0;


void *countgold(void *param)
{
	int i;

	sem_init(&lock, 0, 1);

	printf(GREEN"\n[+]"RESET" In"YELLOW" %s"RESET", Trying to lock via sem_wait 'm'...\n", (char *)param );

	// we call unlock the locked semaphore 'lock'
	sem_wait(&lock);

	printf(YELLOW"%s"RESET" locked the semaphore m\n",(char *)param); 
	printf("In critical section of "RED"%s ^_^\n", (char *)param);

	for (i = 0; i < 1000000; ++i)			//
	{										//  This is the 
		sum += 1;							//	Critical Section 
	}										//

    printf(GREEN"[+]"RESET" In "YELLOW"%s"RESET", Now unlocking via sem_post 'm'...\n\n", (char *)param );
	
	sem_post(&lock);

	return NULL;
}

int main()
{
	pthread_t tid1, tid2;


    printf(GREEN"\n\n=-=-=-=-=-=-   SEMAPHORES    -=-=-=-=-=-=\n\n\n");
	
	
	pthread_create(&tid1, NULL, countgold, "Thread 1");
	pthread_create(&tid2, NULL, countgold, "Thread 2");

	// Wait for both threads to finish
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	fprintf(stderr, GREEN"\n[+]"RESET" Sum is "RED"%d\n\n\n", sum);

return 0;
}
