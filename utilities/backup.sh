#!/usr/bin/env bash

if [ $# -lt 2 ]; then
	echo "Backup utility v1.0"
	echo "Usage $0 <target_path> <zip_name>"
	exit 1
fi

target=$1

# Create a g(z)ipped archive
tar czf "$2" "$1"
