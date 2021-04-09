#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
	close(1);
	int fd = 0;	

	fd = open("log.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR);
	fprintf(stdout, "file descriptor: %d\n", fd);

	puts("Abhinav's log");
	chdir("/usr/bin");				// change the current directory to '/usr/bin'

	execl("/bin/ls", "/bin/ls", ".", (char *)NULL);		// Replace the current process address space
														// with '/bin/ls'
	perror("exec failed!\n");


return 0; 	// This should never execute
}
