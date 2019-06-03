


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>

#include "color.h"

#include "operations.h"


void reccurse_dir_entries(char *location)
{
	struct dirent *dp;
	
    // open up directory
    DIR *dirptr = opendir(location);

    // Read directory entries reccursively until end of directory entries
    while ( ( dp = readdir(dirptr) ) != NULL)
    {
        fprintf(stdout, GREEN"[+]"RESET" Name: "BLUE" %s\n"RESET, dp->d_name);
        print_file_properties(dp->d_name);
    }

    closedir(dirptr);
}

