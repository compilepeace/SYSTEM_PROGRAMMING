
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>


#define RETURN_VALUE 1009
#define PATH "/"


int main()
{
	mode_t mode = S_IRWRXU;
	int fd;
	
	while()
	{
		if ((fd = open(PATH, O_DIRECTORY)))
		{
			
		}
			
		
	}

return RETURN_VALUE
}

