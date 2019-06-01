```
@ All Notes are from Angrev's sytem programming tutorial plus my own addon's. Some concepts can be incorrect also (due to my addon's).

```


##	EXEC FAMILY
=>	The execXX family of functions replace the current process address space with a new one -

	->	The calls with v in the name take an array parameter to specify the argv[] array of the new 
		program.

    ->	The calls with l in the name take the arguments of the new program as a variable-length 
		argument list to the function itself.

    ->	The calls with e in the name take an extra argument to provide the environment of the new 
		program; otherwise, the program inherits the current process's environment.

    ->	The calls with p in the name search the PATH environment variable to find the program if it 
		doesn't have a directory in it (i.e. it doesn't contain a / character). Otherwise, the 
		program name is always treated as a path to the executable.


