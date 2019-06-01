```
@ All Notes are from Angrev's sytem programming tutorial plus my own addon's. Some concepts can be incorrect also (due to my addon's).

```

##	RESOURCE ALLOCATION GRAPH
=>	It tells how the resources are allocated to different processes. A resource aquired by a process is 
	shown by an arrow pointing to the process (from a resource). A process needs a resource is shown by
	an arrow pointing to the resource (from a process).



##	DEADLOCK
=>	Coffman's 4 necessary and sufficient conditions for deadlock are -

		>	Mutual exclusion (i.e. the process should acquire a resource exclusively, not sharing)
		>	Circular wait 
		>	Hold & Wait
		>	No-Preemption (the process should not be interrupted while waiting for a resource).



##	LIVELOCK
=>	When the processes are'nt deadlocked, but are'nt even able to make any progress. 
	Consider a situation - A child is allowed to take a 'pen' and a 'paper' (both or none). If he is able
	to get a pen but unable to get a paper within 10 seconds, he has to keep back the pen also and then
	try again. In a busy system where the paper is never available/vacant, he will continue to wait like
	a dumbass. 
	This condition, where the child is not deadlocked, but also he is not able to make any progress is
	called as a Livelock.



##	FAILED SOLUTIONS

1.	Left-Right Deadlock
2.	Trylock (Leading to a Livelock)



##	VIABLE SOLUTIONS

1.	Arbitrator (Naive and Advanced) (using mutexes)
2.	Leaving the table (Stalling's solution) (using semaphores)
3.	Partial Ordering (Dijkstra's Solution)

