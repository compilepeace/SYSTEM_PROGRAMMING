#!/bin/sh

# Description:
# Write a command or script to recursively find the most recently modified file in a directory. More generally, can you list all files by recency?

# We can list all files by recency using 'ls'
# ls -lAtch .


if [ $# -ne 1 ]; then
	echo "Usage: $0 <search_path>"
	exit 1
fi

search_dir=$1

# find ~ -type f -printf "%T@ %p\n" | sort -n | cut -d' ' -f 2- | tail -n 1
# (man find), see printf 
# -printf : "%T" means time structure tm (see man 3 ctime) "@" is seconds since epoch  
#           "%p" is name current file being iterated
# 
find_newest() {
	echo -e "Searching for newest file in: $1"
	find $1 -type f -printf "%T@ %p\n" | sort -n | cut -d' ' -f 2- | tail -n 1
}

find_oldest() {
	echo -e "Searching for oldest file in: $1"
        find $1 -type f -printf "%T@ %p\n" | sort -n | cut -d' ' -f 2- | head -n 1
}

find_newest $search_dir
find_oldest $search_dir
