```
@ All Notes are from Angrev's sytem programming tutorial plus my own addon's. Some concepts can be incorrect also (due to my addon's).

```

# HEAP (ASLR enabled)

malloc		# Reserves space in heap segment
calloc		# Same as malloc except that it clears the allocated memory to zero
realloc		# Reallocates the space in heap segment.

brk			# sets the end of data segment to the value specified
sbrk		# increments the program's data space. See the man pages for interesting info.
sbrk(0)		# Tells where the heap currently ends (or current location of 'program break')


