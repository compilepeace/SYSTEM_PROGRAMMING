```
@ All Notes are from Angrev's sytem programming tutorial plus my own addon's. Some concepts can be incorrect also (due to my addon's).

```


##	String/character manipulations

strncpy()	- Copies n bytes of string at 'src' to string at 'dest'
strncat()	- Concatenates n bytes of string at 'src' to string at 'dest'
strdup() 	- Returns a malloc'ed copy of the string
strchr()	- Returns a pointer to first character(integer) in the string(haystack).
strstr()	- Same as above but this time it finds the first occurence of string.
strtok()	- String Tokenize (Read man page thoroughly before using).
memcpy()	- copies n bytes starting from 'src' to 'dest'
memmove()	- A safer version of memcpy (works even when the memory regions overlap)


##	2_PROCESSES

fork()
exec()
waitpid()
