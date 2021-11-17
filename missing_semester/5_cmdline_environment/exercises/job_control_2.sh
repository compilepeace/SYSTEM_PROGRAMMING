#!/usr/bin/env sh

# Say you don’t want to start a process until another completes, how you would go about it? In this exercise our limiting process will always be sleep 60 &. One way to achieve this is to use the wait command. Try launching the sleep command and having an ls wait until the background process finishes. 
sleep 5 &
#pgrep sleep | wait && ls		# current session waits for child process to terminate after which it executes 'ls'


# However, this strategy will fail if we start in a different bash session, since `wait` only works for child processes. One feature we did not discuss in the notes is that the `kill` command's exit status will be zero on success and nonzero otherwise. `kill -0` does not send a signal but will give a nonzero exit status if the process does not exist.
# Write a bash function called `pidwait` that takes a pid and waits until the given process completes. You should use `sleep` to avoid wasting CPU unnecessarily.
pidwait () {
	echo "pid: $1"
	for i in $(seq 1 1000); do
		kill -0 "$1" 2> /dev/null	# discard all errors
		if [ $? -ne 0 ]; then		# check the exit code for `kill -0 <pid>` (which returns a 0 if <pid> exists and non-zero exit code if <pid> does not exist.
			ls			# if `kill -0 <pid>` returned a non-zero code, it means <pid> does not exist, then execute 'ls' cmd
			exit 7			# exit with our own indicator status
		else
			echo "sleeping ..."
			sleep 1
		fi
	done
}

pidwait $(pgrep sleep)

