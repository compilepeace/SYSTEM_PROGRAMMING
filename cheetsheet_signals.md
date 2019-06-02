```
@ All Notes are from Angrev's sytem programming tutorial plus my own addon's. Some concepts can be incorrect also (due to my addon's).

```

##	LIST OF USEFUL SIGNALS

SIGINT	- User could send this signal (by Ctrl+c) to stop the process nicely. 
SIGQUIT - Tells the process to stop harshly.
SIGSTOP - You can Pause a process by sending this signal. Freezes the process (no more CPU given)
SIGCONT - To allow a Paused process to Resume execution.
SIGKILL - Send it to terminate a process 


##	TYPES

pid_t			# This type stores the PID of a process (typedef int)
sig_atomic_t	# Ensures that all the bits of the var can be read/modified as an 'Atomic Operation'


##	Terminal Superhero Commands

ulimit -u 40			# To limit maximum number of processes to 40 (small number)
kill -9 -1				# working on fork() remotely, this one's lifesaviour in emergency situation
kill -9 <PID>			# Kill all processes you can kill. Generates a signal SIGKILL (9) 
kill -SIGSTOP <PID>		# Command gives a signal to the process with PID
kill -s <SIGNAL> <PID>	# Send a 'signal (by name)' to the process with pid PID.
kill -l <NUMBER>		# Translate the 'number' into signal name
kill -L					# List available signal choices Table
ps						# Report a snapshot of current process


##	fork-exec-wait Pattern

setrlimit()		# To limit the no. of child processes created
fork()			# Create a process duplicating the parent's process address space
exec()			# execute a program, replacing the parent's process addresss space with new program's
waitpid()		# To wait for child process to finish
wait()			# The parent process will wait until wait(or waitpid) returns 
getenv()		# Returns the value for the Environment variable passed as argument
getpid()		# Returns PID of the currently running process
getppid()		# Returns PID of the parent Process
setenv()		# Sets a new environment variable to its value (both passed as argument to this f())
sleep()			# Takes in no. of seconds as arg and sleeps the process for that much seconds
kill()			# To send any signal to any process/ process group
signal()		# Calls the 'signal-handler' routine on recieving a particular SIGNAL.


##	Interesting MAN Pages

man -s7 signal
