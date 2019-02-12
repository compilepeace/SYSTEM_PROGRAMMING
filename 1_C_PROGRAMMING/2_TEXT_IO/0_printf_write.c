// Printf does'nt explicitly call write until it encounters a newline character '\n' or its buffer
// is full.

// You can check the write syscall by using 'strace' command line tool with the compiled binary.
// $ strace ./a.out

// You'll see 3 write() syscalls

int printf(char *ptr, ...);

int main()
{

	printf("Abhinav is a");	
	printf("Hello there");
	printf("yeas\n");				// Now write() will be called, since it met the newline

	printf("now print\n");			// Again write(), because of '\n'
	printf("Now print again\n");	// Again write() syscall, because of '\n'

}
