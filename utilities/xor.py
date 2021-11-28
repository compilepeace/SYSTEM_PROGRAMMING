#!/usr/bin/env python3

import sys

if (len(sys.argv) < 2):
	print(f"Usage: {sys.argv[0]} <key>")
	exit(1)

# provide a key
key = int(sys.argv[1])
auth = "bmuZo03O4KqWICB}`KOM5VhbwjsahHafAj5C}ma="
 
for c in auth:
		
	print(chr(key^ord(c)), end="")

print()
