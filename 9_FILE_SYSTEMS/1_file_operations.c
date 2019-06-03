// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : Header contains function to print file properties (using struct stat and lstat())


/*

struct stat {
               dev_t     st_dev;     // ID of device containing file 
               ino_t     st_ino;     // inode number 
               mode_t    st_mode;    // protection 
               nlink_t   st_nlink;   // number of hard links 
               uid_t     st_uid;     // user ID of owner 
               gid_t     st_gid;     // group ID of owner 
               dev_t     st_rdev;    // device ID (if special file) 
               off_t     st_size;    // total size, in bytes 
               blksize_t st_blksize; // blocksize for file system I/O 
               blkcnt_t  st_blocks;  // number of 512B blocks allocated 
               time_t    st_atime;   // time of last access 
               time_t    st_mtime;   // time of last modification 
               time_t    st_ctime;   // time of last status change 
           };

*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

#include "color.h"

#include "operations.h"


// This function prints file properties
void print_file_properties(char *filename)
{
	struct stat statbuf;

	// Returns the metadata of the file. If the file is a symbolic link, it returns the info. about 
	// the symlink rather than the file it is pointing to.
	lstat(filename, &statbuf);


	// Printing out the last accessed, modified and status change time
//	fprintf(stdout, BLUE"\n\t\t=-=-=-=-=- FILE PROPERTIES -=-=-=-=-=\n\n"RESET);
	fprintf(stdout, GREEN"\t[+]"RESET" Last accessed \t\t:"GREEN" %s"RESET, ctime( &(statbuf.st_atime)) );
	fprintf(stdout, GREEN"\t[+]"RESET" Last modified \t\t:"GREEN" %s"RESET, ctime( &(statbuf.st_mtime)) );
    fprintf(stdout, GREEN"\t[+]"RESET" Last status change time \t:"GREEN" %s"RESET, ctime( &(statbuf.st_ctime)) );

	
	// Printing out the inode number
	fprintf(stdout, GREEN"\t[+]"RESET" Inode number \t\t:"GREEN" %ld\n"RESET, statbuf.st_ino );
    fprintf(stdout, GREEN"\t[+]"RESET" User ID \t\t\t:"GREEN" %d\n"RESET, statbuf.st_uid );
    fprintf(stdout, GREEN"\t[+]"RESET" Group ID \t\t\t:"GREEN" %d\n"RESET, statbuf.st_gid );
    fprintf(stdout, GREEN"\t[+]"RESET" Number of hard links \t:"GREEN" %ld\n"RESET, statbuf.st_nlink);
	fprintf(stdout, GREEN"\t[+]"RESET" Size (in bytes) \t\t:"GREEN" %ld\n"RESET, statbuf.st_size );
    fprintf(stdout, GREEN"\t[+]"RESET" Block size \t\t\t:"GREEN" %ld\n"RESET, statbuf.st_blksize );


	fprintf(stdout, "\n");
}
