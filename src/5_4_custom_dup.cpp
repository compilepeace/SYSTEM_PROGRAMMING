/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : custom_dup.cpp                                                    *
 *                                                                              *
 * Description: Custom implementation to dup and dup2 via fcntl().              *
 *                                                                              *
 ********************************************************************************/

#include <sys/stat.h>       /* for open */
#include <fcntl.h>
#include <unistd.h>         /* for write */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#define FILENAME "temporary_file"

int custom_dup (int oldfd);
int custom_dup2 (int oldfd, int newfd);

int main (int argc, char **argv) {
    
    int fd, returned_fd;

    if (argc != 2 || strcmp (argv[1], "--help") == 0) {
        fprintf (stderr, "Usage: %s <dup|dup2>\n", argv[0]);
        return 1;
    }
    
    fd = open (FILENAME, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fd < 0) {
        perror ("while opening file");
        return 1;
    }

    if (write (fd, "prologue, ", 10) != 10) {
        perror ("error while writing to file");
        return 1;
    }

    if (strncmp (argv[1], "dup2", 4) == 0) {

        returned_fd = custom_dup2 (fd, 10);
        if (write (returned_fd, "dup2 did\n", 9) < 0) {
            perror ("write failed");
            return 1;
        }
    }
    else if (strncmp (argv[1], "dup", 3) == 0) {

        returned_fd = custom_dup (fd);
        if (write (returned_fd, "dup() did\n", 8) < 0) {
            perror ("write failed");
            return 1;
        }
    }

    else {
        fprintf (stderr, "Usage: please supply argv[1] starting with either dup or dup2\n");
    }

    return (close (fd) == -1) ? 1: 0;
}


int custom_dup (int oldfd) {
    int fd;

    fprintf (stderr, "Inside %s(%d)\n", __FUNCTION__, oldfd);
    
    // oldfd may not be open in the first place
    if (fcntl (oldfd, F_GETFL) == -1) {
        errno = EBADF;
        return -1;
    }
    
    return fcntl (oldfd, F_DUPFD, 0);
}

int custom_dup2 (int oldfd, int newfd) {
    int ret_fd;

    fprintf (stderr, "Inside %s(%d, %d)\n", __FUNCTION__, oldfd, newfd);


    // If oldfd is not already an open file descriptor
    if (fcntl (oldfd, F_GETFL) < 0) {
        errno = EBADF;
        return -1;
    }

    // If oldfd and newfd are already equal, do nothing
    if (newfd == oldfd) 
        return newfd;

    // If newfd is already open fd, close (newfd)
    if (fcntl (newfd, F_GETFL) > 0) {
        close (newfd);
    }

    return fcntl (oldfd, F_DUPFD, newfd);
}