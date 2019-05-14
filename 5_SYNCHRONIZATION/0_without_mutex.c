// Example taken from https://github.com/angrave/SystemProgramming/wiki/Synchronization%2C-Part-1%3A-Mutex-Locks#simplest-complete-example


#include <stdio.h>
#include <pthread.h>

#include "color.h"



int sum = 0;


void *countgold(void *param)
{
	int i;

	for (i = 0; i < 1000000; ++i)			//
	{										//  This is the 
		sum += 1;							//	Critical Section 
											//
        fprintf(stdout, GREEN"[+]"YELLOW" %s"RESET" : "RED"%d \n", (char *)param, sum);
	}										

	return NULL;
}

int main()
{
	pthread_t tid1, tid2;
	
	pthread_create(&tid1, NULL, countgold, "Thread 1");
	pthread_create(&tid2, NULL, countgold, "Thread 2");

	// Wait for both threads to finish
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);

	fprintf(stderr, "[+] Without mutex/lock, sum : %d\n", sum);
}
