// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : This program leverages directory functions/operations (opendir, readdir, closedir) to
//				 reccurse through directory contents


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>

#include "color.h"

#include "operations.h"


int main(int argc, char *argv[])
{
	
	// Check for command line arguments
	if (argc < 2)
	{
		fprintf(stderr, RED"[-]"YELLOW" Usage: %s <dir_path>\n", argv[0]);
		exit(0x10);
	}	


	reccurse_dir_entries(argv[1]);


return 0;
}

