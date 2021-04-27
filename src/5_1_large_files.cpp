/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : large_files.cpp                                                   *
 *                                                                              *
 * Description: This program creates files larger than 2**32 using holes.       *
 *                                                                              *
 ********************************************************************************/
#define _FILE_OFFSET_BITS 64

#include <cstdio>          
#include <cstring>          /* for strcmp */
#include <stdlib.h>         /* for atol */
#include <sys/stat.h>       /* for open | creat */
#include <fcntl.h>
#include <unistd.h>         /* for write */

int main (int argc, char **argv) {

    int fd;
    off_t offset;

    if (argc != 3 || strcmp(argv[1], "--help") == 0) {
        fprintf (stderr, "[-] Usage <filename> <offset>\n");
        return 1;
    }

    fd = open (argv[1], O_RDWR|O_CREAT, S_IRUSR|S_IWUSR);
    if (fd == -1) {
        perror ("while creating file");
        return 1;
    }

    offset = atol (argv[2]);
    fprintf (stderr, "%lld\n", (long long) offset);
    if (lseek (fd, offset, SEEK_SET) == -1) {
        perror ("while lseek'ing to offset");
        return 1;
    }

    if (write (fd, "Abhi", 4) != 4) {
        perror ("while writing to file");
        return 1;
    }

    close (fd);
    return 0;
}