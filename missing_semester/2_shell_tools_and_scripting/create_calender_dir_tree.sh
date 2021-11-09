#!/usr/bin/env bash

# Author: Abhinav Thakur
# Email : compilepeace@gmail.com
# 
# Description: makes a directory tree using 'shell expansion' "$1"/{1..12}/{1..31}
# 
# for debugging: use shellcheck (sudo apt install -y shellcheck)

root_dir=$1


if [[ "$#" -lt 1 ]]; then
	echo "Usage: "$0" test_dir_name"
	exit
fi

echo "Creating a calender directory tree with root node naming: $root_dir"


mkdir -p "$1"/{1..12}/{1..31}
#if [[ $(mkdir "$1"/{1..12}/{1..31}) - 1 ]]; then
if [[ $? -ne 0 ]]; then
	echo "mkdir didn't end successfully"
	echo "hahaha ends"
	exit
fi

echo "khatam"
