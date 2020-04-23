//
// This program is taken as an example from the course.
//
// Description	:	This program demonstrates the blockage of pipes. Pipes have fixed/limited buffer 
//				 	capacity. If the pipe if full, writing process will be blocked. Therefore, it 
//					needs to be flushed time-to-time if used in this fashion.
//
// $ cat /proc/version
// In my OS (Ubuntu 18.10, Linux version 4.15.0-47-generic), 65520 bytes can be accumulated into a
// pipe.

// NOTE : Data written to the write end of the pipe is buffered by the  kernel until it is read from
// the read end of the pipe

#include <unistd.h>
#include <stdio.h>

#include "color.h"

#define MSG "I am Mahakaal\n"


int main()
{
	int fds[2];
	
	pipe(fds);

	int bytes = 0;

	while(1)
	{
		printf(YELLOW"%d\n", bytes);

		// MSG gets written to fds[1] (output side of pipe) which should be used up by the input
		// side of the pipe - fds[0] by some other process. Since no process is using fds[0], the 
		// data bytes of o/p gets accumulated into the pipe and when it reaches the maximum capacity
		// of pipe, no outputs can be written to pipe.
		write(fds[1], MSG, sizeof(MSG));
		bytes += sizeof(MSG);
	}

return 0;
}
