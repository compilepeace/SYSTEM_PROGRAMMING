#!/usr/bin/env sh

if [ $# -ne 1 ]; then
	echo -e "Usage: $0 \"cmdline_process_invokation\"" # eg: python3 ./interruptme
	exit 1
fi

ps aux | grep -E "$1" | awk '{print $2}' | xargs kill -s 9 

