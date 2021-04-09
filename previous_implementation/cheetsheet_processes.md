



##  fork-exec-wait Pattern

setrlimit()     # To limit the no. of child processes created
fork()          # Create a process duplicating the parent's process address space
exec()          # execute a program, replacing the parent's process addresss space with new program's
waitpid()       # To wait for child process to finish
wait()          # The parent process will wait until wait(or waitpid) returns
getenv()        # Returns the value for the Environment variable passed as argument
getpid()        # Returns PID of the currently running process
getppid()       # Returns PID of the parent Process
setenv()        # Sets a new environment variable to its value (both passed as argument to this f())
sleep()         # Takes in no. of seconds as arg and sleeps the process for that much seconds
kill()          # To send any signal to any process/ process group
signal()        # Calls the 'signal-handler' routine on recieving a particular SIGNAL.


