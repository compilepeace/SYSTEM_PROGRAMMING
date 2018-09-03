
// Have a look at the man page of open() syscall. 
// $ man open 					# This will do for 32 bit linux
// $ man 2 open					# This will do for 64 bit linux


#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


#include <stdio.h>


#define PATH "./dummy.txt"

int main()
{
	mode_t mode = S_IRWXO;
	
		unsigned int fd = open(PATH , O_CREAT | O_APPEND | O_RDWR, mode);
	
		// printf() will flush the buffer whenever it encounters the '\n' character
		// i.e. printf() will call the write() whenever it'll encounter the '\n' character
		// and flush the buffer to corresponding file descriptor.
		printf("The file descriptor assigned to opened file is : %d\n", fd);	
		write(fd, "Hello\n", 6);
		close(fd);
		printf("Message written to the " PATH "\n");

return 0;
}
