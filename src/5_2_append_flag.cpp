/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : append_flag.cpp                                                   *
 *                                                                              *
 * Description: This program demonstrates usefulness of O_APPEND flag           *
 *                                                                              *
 ********************************************************************************/

#include <sys/stat.h>       /* for open */
#include <fcntl.h>
#include <unistd.h>         /* for write */
#include <stdio.h>
#include <string.h>


int main (int argc, char **argv) {

    int fd;

    if (argc != 2 || strcmp (argv[1], "--help") == 0) {
        fprintf (stderr, "Usage: %s <filename>", argv[0]);
        return 1;
    }

    fd = open (argv[1], O_RDWR|O_APPEND);
    if (fd == -1) {
        perror ("while opening file");
        return 1;
    }

    if (lseek (fd, 0, SEEK_SET) == -1) {
        perror ("while lseek'ing to file");
        return 1;
    }

    // the writes will happen to the EOF regardless of where the current file pointer
    // for the file desription resides as O_APPEND flag is used to open file.
    if (write (fd, "stamped", 7) != 7) {        
        perror ("while writing to file");
        return 1;
    }

    close (fd);
    return 0;
}