// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : Passing stack variables (automatic variables) to the thread. We observed that if we
//				 don't use pthread_join() to wait for the thread completion, the function 
//				 start_thread() returns before the thread 'myfunc' creates its stack frame. Hence, 
//				 start_thread() destroy's its stack frame (which includes the variable passed to the
//				 thread - 'argument') and its automatic variables become unavailable. Therefore we 
// 				 need to take proper care of waiting for the thread's completion when we pass 
//				 automatic variables.


#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "color.h"

void *myfunc(void *ptr)
{
	// An audible bell 'ASCII code 0x7' is passed to myfunc, so the program beeps after this thread
	// executes.
	fprintf(stdout, BOLDGREEN"\n[+]"RESET " In function %s : %s \n", __FUNCTION__, (char *)ptr);
	return NULL;
}


pthread_t start_thread()
{
	pthread_t tid;
	int argument = 0x7;

	void *ret_value;

	pthread_create(&tid, NULL, myfunc, &argument);
	
	// Without pthread_join(), start_thread() won't wait for the new thread 'myfunc' to finish and
	// will exit before the new thread starts preparing its stack frame.
	pthread_join(tid, &ret_value);

	return tid;
}

int main()
{

	pthread_t id = start_thread();	

	fprintf(stdout, GREEN"\t[+]"RESET " Thread returned id : %ld \n\n", id);

return 0;
}
