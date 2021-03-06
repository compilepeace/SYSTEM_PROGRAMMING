```
@ All Notes are from Angrev's sytem programming tutorial plus my own addon's. Some concepts can be incorrect also (due to my addon's).

```

NOTE :	Include -pthread (or -lthread) as compiler option to tell the compiler we need threading
		support. Include <pthread.>


clone					# Creates a child process in a manner similar to fork().
pthread_create			# Create a process thread
pthread_join			# [+] Wait for your thread to finish and then return and continue executing main.
pthread_cancel			# Sends a cancellation request to the thread
pthread_exit			# Terminates the calling thread, i.e. the thread never returns after calling it.
						# After executing child thread, it exits the process too. Creates thread zombies
pthread_yield			# Causes the calling thread to free the CPU.


##	LOCK OR MUTEX (MUTual EXclusion)
=>	If you lock a mutex, it does'nt stop all other threads. Its only when a thread attempts to lock a 
	mutex that is already locked, will the thread have to wait. Its common to have one lock per data 
	structure you need to update.

pthread_mutex_lock		# Place this function at the start of critical section to lock a shared resource
pthread_mutex_unlock	# Place this function at the end of critical section to unlock a shared resource 
pthread_mutex_destroy	# To destroy an mutex. NOTE: you can only destroy an unlocked mutex.
pthread_mutex_init		# To create a mutex


##	SEMAPHORES

sem_init				# Initializes an unnamed semaphore by a value.
sem_wait				# waits if count is 0 & decrement count by one and returns if count != 0. (lock)
sem_post				# Anounce that we've finished (like unlock() in mutex)



##	CONDITION VARIABLES
=>	These allow a set of threads to sleep until tickled/woken up. You also can't wake threads directly
	instead you 'signal' the condition variable, which then will wake up one/all threads that are 
	sleeping inside the condition variable. These are used with a mutex and a loop (to check a 
	condition).

	SPURIOUS WAKEUP : Occasionally a waiting thread may appear to wake up for no reason. This is called
					  spurious wakeup. 

pthread_cond_broadcast	# Wake up all threads sleeping inside a condition variable
pthread_cond_signal		# Wake up one thread sleeping inside a condition variable (NOT POSIX signals)
pthread_cond_wait		# unlock the mutex, wait (sleep until pthread_cond_signal is called on the same
						# thread) and before returning locks the mutex.




##	TO USE A SEMAPHORE AS A MUTEX
=>	The overhead of semaphore is greater than that of mutex.

	*	Initialize the semaphore with a count of one (with sem_init).
	*	Replace "pthread_mutex_lock" with "sem_wait"
	*	Replace "pthread_mutex_unlock" with "sem_post"

sem_t s;
sem_init(&s, 0, 1);

sem_wait(&s);
	// Critical Section
sem_post(&s);


##	MACROS

PTHREAD_MUTEX_INITIALIZER	# Similar to pthread_mutex_init() 


