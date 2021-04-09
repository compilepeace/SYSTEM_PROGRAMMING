/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : cp_holes.cpp                                                      *
 *                                                                              *
 * Description: A custom implementation of cp command with some additional      *
 *              features.                                                       *
 *                                                                              *
 * NOTE: The cp command copies the file preserving the holes of input file in   *
 *       output file.                                                           *
 *                                                                              *
 ********************************************************************************/

#include <vector>

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include <sys/stat.h>       /* for open/creat */
#include <fcntl.h>          
#include <unistd.h>         /* for read/write/close/lseek */


void usage_error (char *);


int main (int argc, char *argv[]) {

    /*  read the input file and write to target file until a '\x00' is encountered,
        when a NULL byte is encountered, stop writing to target file and
        start a NULL counter until we hit a byte other than NULL.
        Now lseek() to counter value from the end of 'file's read/write pointer'
        and repeat the above process again until an EOF is encountered and read()
        returns a 0.
    */

    mode_t tfile_perms;
    int ifd, tfd;
    size_t bytes_read, null_counter = 0;
    uint8_t ch;
    std::vector <uint8_t> input_buffer;

   
    if (argc != 3 || strncmp(argv[1], "--help", strlen("--help")) == 0)
        usage_error (argv[0]);

    // open input file
    ifd = open (argv[1], O_RDONLY);
    if (ifd == -1) {
        perror ("while opening input file");
        exit (EXIT_FAILURE);
    }

    // crate target file
    tfile_perms = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
    tfd = open (argv[2], O_CREAT | O_RDWR | O_TRUNC, tfile_perms);
    if (tfd == -1) {
        perror ("while opening target file");
        exit (EXIT_FAILURE);
    }

    // read from input file and write to target file
    while ( (bytes_read = read(ifd, &ch, 1)) == 1) {
        
        if (ch == '\x00') {
            // flush input_buffer to file
            if (input_buffer.size() != 0) {
                // write input buffer to file
                if (write (tfd, &input_buffer[0], input_buffer.size()) < 0) {
                    perror ("while writing characters to target file");
                    exit (EXIT_FAILURE);
                }
                // resize input buffer to 0
                input_buffer.resize(0);
            }
            ++null_counter;
        }
        
        else {
            if (null_counter != 0) {
                // lseek target file to create a hole
                if (lseek (tfd, null_counter, SEEK_CUR) == -1) {
                    perror ("lseek failed to create a hole");
                    exit (EXIT_FAILURE);
                }
                null_counter = 0;
            }
            input_buffer.push_back(ch);
        }
    }

    // if no non-null character was found
    if (null_counter != 0) {
        // lseek target file to second last byte.
        if (lseek (tfd, null_counter-1, SEEK_CUR) == -1) {
            perror ("[] lseek failed to create a hole");
            exit (EXIT_FAILURE);
        }
        // write a 0 byte at the end of file (last byte) to create a hole
        if (write (tfd, "\x00", 1) == -1) {
            perror ("[] while writing a NULL char to EOF");
            exit (EXIT_FAILURE);
        }
    }

    if (input_buffer.size() != 0) {
        if (write (tfd, &input_buffer[0], input_buffer.size()) < 0) {
            perror ("[] while writing to target file");
            exit (EXIT_FAILURE);
        }
    }

    if (bytes_read == -1) {
        perror ("while reading from input file");
        exit (EXIT_FAILURE);
    }
    else if (bytes_read == 0)
        fprintf (stderr, "EOF reached: copied successfully");


    if (close (ifd) == -1) {
        perror ("while closing input file");
        exit (EXIT_FAILURE);
    }

    if (close (tfd) == -1) {
        perror ("while closing target file");
        exit (EXIT_FAILURE);
    }

    exit (EXIT_SUCCESS);
}


void usage_error (char *program_name) {
    fprintf (stderr, "Usage Error: %s <source_file> <destination_file>", program_name);
    exit (EXIT_FAILURE);
}