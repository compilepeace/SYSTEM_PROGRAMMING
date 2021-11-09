#!/bin/bash

# Author: Abhinav Thakur
# Email : compilepeace@gmail.com
#
# Description: 	Shell scripting is suitable for shell-related tasks. This script documents 
#		some shell scripting syntax. 
#
# For debugging: use shellcheck (sudo apt install -y shellcheck)
# 

# variable declaration
find_val=$1
filename=$2

if [[ $# -lt 2 ]]; then
	echo "$(date): Running program $0 with $# arguments having [pid $$]"
	echo "Usage: $0 pattern file..."
	exit
fi	

# function definition
find_pattern () {
	# illustrates command substitution $(cmd)
	echo -e "find_pattern($1, $2) \nwhere \$@ expands to: $@"
	grep $1 $2 > /dev/null 2> /dev/null
	# when pattern is not found, grep has a non-zero exit status
	# man test (for test flags like -ne)
	if [[ "$?" -ne 0 ]]; then
		echo "File $2 does not have any $1, appending $1 to $2"
		echo "# $1" >> "$2"
	fi
}

# Loop constructs
# NOTE: {1..5} this expansion works with BASH (not with sh)
# The "$@" will expand to all the arguments provided except argv[0] (args in context to the script not function)
for i in "$@"; do
	echo $i
done

# function calls
find_pattern "$find_val" "$filename"
