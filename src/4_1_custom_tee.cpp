/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : custom_tee.cpp                                                    *
 *                                                                              *
 * Description: A custom implementation of tee command. tee takes input from    *
 *              STDIN_FILENO till EOF is encountered and writes it to a file    *
 *              as well as STDOUT_FILENO.                                       *
 *                                                                              *
 * NOTE: By default it overwrites the output file (if any exists by the same    *
 *       name). Also '-a' option is implemented to allow appending to an        *
 *       already existing file by the same name.                                *
 *                                                                              *
 ********************************************************************************/

#include <vector>
#include <iostream>

#include <stdio.h>
#include <string.h>         /* for strncmp */
#include <stdlib.h>         /* EXIT_FAILURE and EXIT_SUCCESS */
#include <stdint.h>         /* defines uintn_t */

#include <sys/stat.h>       /* for open/creat */
#include <fcntl.h>
#include <unistd.h>         /* for read/write */


void usage_error (const char *);
void parse_options (const int , char **, char *&, int *);

int main (int argc, char *argv[]) {

    std::vector <uint8_t> input_buffer;
    mode_t file_perms;
    int ret_value, fd, open_flags;
    uint8_t byte_read;
    char *filename;


    // either user asked for a help or didn't provide enough arguments to the command, display usage error
    if (argc < 2 || (strncmp(argv[1], "--help", sizeof("--help")) == 0))
        usage_error (argv[0]);

    parse_options (argc, argv, filename, &open_flags);

    // read input from STDIN_FILENO into input buffer (vector) until EOF is encountered
    while ( (ret_value = read (STDIN_FILENO, &byte_read, 1)) == 1) {
        input_buffer.push_back(byte_read);
    }

    if (ret_value == -1) {
        perror ("while reading from STDIN");
        exit (EXIT_FAILURE);   
    } 

    // open output file
    file_perms = S_IRUSR | S_IWUSR | S_IXUSR | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;
    fd = open (filename, open_flags, file_perms);
    if (fd == -1) {
        perror ("while opening output file");
        exit (EXIT_FAILURE);
    }

    // write to output file
    if ( ( ret_value = write (fd, &input_buffer[0], input_buffer.size())) != input_buffer.size()) {
        if (ret_value == -1)
            perror ("while writing to output file");
        else 
            fprintf (stderr, "%ld bytes written instead of %ld\n", (long ) ret_value, input_buffer.size());
        exit (EXIT_FAILURE);
    }

    // write to STDOUT
    if ( (ret_value = write (STDOUT_FILENO, &input_buffer[0], input_buffer.size())) != input_buffer.size()) {
        if (ret_value == -1)
            perror ("while writing to STDOUT");
        else
            fprintf (stderr, "%ld bytes written instead of %ld\n", (long ) ret_value, input_buffer.size());
        exit (EXIT_FAILURE);
    }  

    // release resources
    if (close (fd) == -1)
        perror ("while closing output file");
    
    exit (EXIT_SUCCESS);
}


void parse_options (const int argc, char **argv, char * &filename, int *open_flags) {
    
    int optchar;
    bool append = false;

    /* Another way to prevent getopt from permuting command line arguments (and hence remain portable)
       is by putting a '+' sign at the beginning of 'optstring' parameter of getopt() call.
        see getopt() prototype for 'optstring' parameter.
    */
    if (setenv ("POSIXLY_CORRECT", "set for portability of getopt", 0) == -1) 
        perror ("while setting environment variable POSIXLY_CORRECT");


    /*
        extern char *optarg;
        extern int optind, opterr, optopt;

        int getopt(int argc, char * const argv[], const char *optstring);
    */
    while ( (optchar = getopt(argc, argv, "+:a")) != -1 ) {
        /*  '+' char in  optstring above is for portability reasons
            ':' char after '+' is to supress getopt() default error messages
        
            Optional argument (2 colons after option character)
            optstring - "a::" means -a <optional_argument> 
        */

        /* there are 2 errors associated with getopt(), i.e.
            1. Unrecognized Option
            2. Missing Argument
            see getopt return values '?' and ':' for handling part.
        */

        switch (optchar) {
            case 'a':   /* append mode 
                            If this option were to take any argument, it would get stored
                            in the global variable 'optarg'.
                        */
                        append = true;
                        break;
            
            case '?':   /* 
                        > 'Unrecognized Option' character encountered & stored in optopt. 
                        opterr = 1 (by default), if we set opterr = 0, it will surpress
                        error messages printed by getopt(). This is used to display 
                        customized error messages.
                        Another way to supress getopt() error messages is to put a ':'
                        character at the start of 'optstring' parameter.
                        */
                        fprintf (stderr, "Unrecognizable option: %c\n", optopt);
                        break;
            
            case ':':   /*
                        > 'Missing Argument'
                        */
                        fprintf (stderr, "missing argument error\n");
                        break;
            default:
                        usage_error (argv[0]);
        }
    }

    // argv[optind] is NULL if end of argument list is reached
    if (optind < argc && argv[optind] != NULL)
        filename = &argv[optind][0];
    else 
        usage_error (argv[0]);
    

    *open_flags = O_CREAT | O_WRONLY;
    if (append)
        *open_flags |= O_APPEND;
    else
        *open_flags |= O_TRUNC; 
}

void usage_error (const char *prog_name) {
    fprintf (stderr, "%s [--options] <filename>\n", prog_name);
    exit (EXIT_FAILURE);
}