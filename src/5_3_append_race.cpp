/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : append_race.cpp                                                   *
 *                                                                              *
 * Description: This program demonstrates the race condition occuring without   *
 *              O_APPEND flag.                                                  *
 *                                                                              *
 * Run it 2 times -                                                             *
 * ./a.out xxxx 10000 x & ./a.out xxxx 10000 x      (size of xxxx < 20000)      *
 * ./a.out yyyy 10000 & ./a.out yyyy 10000          (size of yyyy - 20000)      *
 ********************************************************************************/

#include <sys/stat.h>       /* for open */
#include <fcntl.h>
#include <unistd.h>         /* for write */
#include <stdio.h>
#include <stdlib.h>         /* for atol */
#include <string.h>


int main (int argc, char **argv) {

    long long ncount = 0;
    int fd;
    char ch;

    if (argc < 3 || strcmp (argv[1], "--help") == 0) {
        fprintf (stderr, "Usage: %s <filename> <nbytes>\n", argv[0]);
        return 1;
    }

    // Do not open in append mode if 4th cmd line argument is supplied
    if (argc == 4) {
        fd = open (argv[1], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        ch = 'B';
    }
    // Default: open in append mode, write character - 'A'
    else {
        fd = open (argv[1], O_RDWR|O_CREAT|O_APPEND, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
        ch = 'A';      
    }

    if (fd == -1) {
        perror ("while opening file for reading/writing");
        return 1;
    }

    ncount = atol (argv[2]);

    // write argv[2] number of character to fd
    if (ch == 'A') {
        for (int i = 0; i < ncount; ++i) {
            if (write (fd, &ch, 1) == -1) {
                perror ("while writing to file");
                return 1;
            }
        }
    }
    else {
        for (int i = 0; i < ncount; ++i) {
            if (lseek (fd, 0, SEEK_END) == -1) {
                perror ("while lseek'ing to EOF");
                return 1;
            }
            if (write (fd, &ch, 1) == -1) {
                perror ("while writing to file");
                return 1;
            }
        }
    }

    close (fd);
    return 0;
}