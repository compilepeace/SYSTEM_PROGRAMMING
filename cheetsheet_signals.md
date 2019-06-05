```
@ All Notes are from Angrev's sytem programming tutorial plus my own addon's. Some concepts can be incorrect also (due to my addon's).

```

##  C POSIX call for signals

kill()          # To send any signal to any process/ process group
signal()        # Calls the 'signal-handler' routine on recieving a particular SIGNAL. Used to change
				#signal deposition
sleep()         # Takes in no. of seconds as arg and sleeps the process for that much seconds


##	LIST OF USEFUL SIGNALS
A signal allows one process to asynchronously send a signal/message to another process.

SIGINT	- User could send this signal (by Ctrl+c) to stop the process nicely. (can be caught) 
SIGQUIT - Tells the process to stop harshly.
SIGSTOP - You can Pause a process by sending this signal. Freezes the process (no more CPU given)
SIGCONT - To allow a Paused process to Resume execution.
SIGKILL - Send it to terminate a process (Cannot be caught) 


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



##	Check return value of child process (2 MACROS) (https://github.com/angrave/SystemProgramming/wiki/Process-Control%2C-Part-1%3A-Wait-macros%2C-using-signals)

WIFEXITED()
WEXITSTATUS()


##	Interesting MAN Pages

man -s7 signal

