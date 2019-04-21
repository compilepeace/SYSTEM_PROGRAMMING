// Why in the above code, printf() shows output twice even when fork() is called after printf() ??

#include <unistd.h>
#include <stdio.h>

int main()
{
	
	// Printf() is called but the process buffer is not yet flushed, hence when fork() is called, 
	// the entire process's memory is duplicated including the buffer. The output text is therefore
	// still in the buffer waiting to be sent out. Thus, the child process whose memory address space
	// still contains the output string flushes the buffer as the main() terminates. Since at the
	// program termination, whole process buffer is flushed out. You can flush the buffer manually
	// by using '\n' or fflush().
	printf("How did you threw me twice on stdout ??");
	fork();

return 0;
}
