
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define PATH "./dummy1.txt"

int main()
{

	mode_t mode = S_IRWXU; 

	close(1);				// close the file descriptor 1 (i.e. currently for STDOUT)
							// Now open() will open the file and associate the file with
							// the shortest possible file descriptor available, which here
							// is 1.		


	int fd = open(PATH, O_CREAT | O_APPEND | O_RDWR, mode );
	
	
	if (fd == -1)
	{
		perror("open()");
		exit(1);
	}

		// Since printf() is a wrapper function and uses write() syscall internally (which takes
		// file descriptor as its first argument) and that printf() gives write() sycall '1' as 
		// its first argument...
		// But wait!! file descriptor 1 is associated with the opened file at PATH, 
		// Therefore printf() will write its output to file descriptor 1, which is associated with
		// the opened file at path PATH.
		//
		// write(1, "File descriptor fd : 1\n", 23) = -1 EBADF (Bad file descriptor),
		// i.e. when printf() calls write() syscall, it returns -1 stating Bad FD and therefore
		// does not write to it (fd 1).	
		fprintf(stderr, "File descriptor fd : %d\n", fd);
		write(fd, "bye\n", 4);
		close(fd);	

	

return 0;
}
