
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>
#include <stdlib.h>

#define PATH "./errors.txt"

int main()
{

	mode_t mode = S_IRWXU; 

	close(2);				// close the file descriptor 2 (i.e. currently for STDERR)
							// Now open() will open the file and associate the file with
							// the shortest possible file descriptor available, which here
							// is 2 (Since it is not in use).		


	int fd = open(PATH, O_CREAT | O_TRUNC | O_RDWR, mode );			// The file "errors.txt" is now 
																	// associated with fd 2.	
	
	if (fd == -1)
	{
		perror("open()");			// perror() redirects messages to file descriptor 2 
		exit(1);
	}

	
	int fd2 = open("", O_RDWR | O_TRUNC, mode); 		// Intentional bug
	
	if (fd2 == -1)
	{
		perror("open fd2()");		// perror() redirects messages to file descriptor 2
		exit(1);					// which right now is associated with "errors.txt"
	}
	
	fprintf(stderr, "Hello error");	
	close(fd);	

	

return 0;
}
