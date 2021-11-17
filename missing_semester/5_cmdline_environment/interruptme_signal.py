#!/usr/bin/env python3
import signal, time

# type 'Ctrl+\' to deliver a SIGQUIT when 'Ctrl+c' doesn't work
# Some signals cannot be caught (for eg: SIGKILL), but one should not use it as it leaves
# the child processes in alive orphan state which could have a weird behavior
# If you're in SSH connection and you logoff, a SIGHUP (hangup signal) is delivered which 
# ensures the termination of processes (parent as well as the child processes)
# Ctrl+z (SIGSTOP) : makes a program suspend (like $sleep 1000 &)
def handler (signum, time):
	print ("\nI got a SIGINT, but I am not stopping")


signal.signal(signal.SIGINT, handler)

i=0
while True:
	time.sleep(.1)
	# carriage return '\r' moves the cursor to the beginning of the line without advancing the line
	print(f"\r{i}: haha", end="")
	i += 1
