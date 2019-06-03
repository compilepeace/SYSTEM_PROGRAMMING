// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : This module contains all the operations that are being performed on directories


#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>

#include "color.h"

#include "operations.h"


void getfiletype_wrapper(char *, char *);
void reccurse_dir_entries(char *);


void reccurse_dir_entries(char *location)
{
	struct dirent *dp;
	
    // open up directory
    DIR *dirptr = opendir(location);
	if ( dirptr == NULL )
	{
		perror(RED"[-]"RESET" While 'reccurse_dir_entries' in opendir(): ");
		exit(0x30);		
	}


    // Read directory entries reccursively until end of directory entries
    while ( ( dp = readdir(dirptr) ) != NULL)
    {
        fprintf(stdout, GREEN"[+]"RESET" Name: "BLUE" %s\n"RESET, dp->d_name);
        print_file_properties(dp->d_name);

		// get filetype of this particular directory entry
		getfiletype_wrapper(location, dp->d_name);			
	}

	// Prevent resource leak
    closedir(dirptr);
}



// A wrapper function that sets up absolute pathname for directory entry's and calls getfiletype() on
// that directory entry
void getfiletype_wrapper(char *user_provided_location, char *dir_entry)
{
        // To get proper results (i.e. filetype from getfiletype's S_ISBLK() etc.) use the absolute
        // pathname for file (i.e. from / directory) to identify correct file type, otherwise we 
        // won't get proper filetype.       
        char absolute_path[300];
        int location_len = strlen(user_provided_location);

        // Zero out absolute path and store user provided location
        memmove(absolute_path, "0", sizeof(absolute_path));     
        strncpy(absolute_path, user_provided_location, location_len);    

        // Append a '/' at the end of location provided by user
        if (absolute_path[location_len - 1] != '/')
            strncat(absolute_path, "/", 1);     

        // Append directory entry
        strncat(absolute_path, dir_entry, strlen(dir_entry));

        // Finally send the absolute path of directory entry to getfiletype()
        getfiletype(absolute_path);
}
