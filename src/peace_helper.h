/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : peace_helper.h                                                    *
 *                                                                              *
 * Description: This module provides an API to most commonly used helper        *
 *              functions, external variable declarations and some useful macro *
 *              definitions.                                                    *
 *                                                                              *
 ********************************************************************************/


#ifndef _PEACE_HELPER_HDR_H
#define _PEACE_HELPER_HDR_H     /* prevent accidental multiple inclusions */

#include <stdio.h>              /* standard I/O functions */
#include <sys/types.h>          /* standard data type definitions (portability concern) */
#include <sys/stat.h>           
#include <sys/fcntl.h>
#include <stdint.h>
#include <stdlib.h>             /* prototypes for library functions along with definitions for EXIT_SUCCESS & EXIT_FAILURE macros */
#include <unistd.h>             /* prototypes for system calls */
#include <errno.h>              /* Declares errno and defines error constants */
#include <string.h>             /* Commonly used string-handling functions */

#define min(a,b)    ((a) < (b) ? (a) : (b))
#define max(a,b)    ((a) > (b) ? (a) : (b))

typedef enum {FALSE, TRUE} Boolean;     /* defining Boolean type */


/* ____ add shared|external data */
extern int logfd;                       /* file descriptor to generate debug logfile (if --log option is specified)


/* -x-x-x-x-x-x-x-x-x-x-x-x- Exported API -x-x-x-x-x-x-x-x-x-x-x-x- */

/********************************************************************
 *                                                                  *
 * NOTE: Below are the functions exported by respective object      *
 *       files. Functions internal to these object files are        *
 *       declared inside the respective source files.               *
 *                                                                  *
 ********************************************************************/

/* peace_helper.o */
void errUsrMsg                      (const char *srcFile, const char *errFuncName, int lineNum, const char *format, ...);
void errSysMsg                      (const char *srcFile, const char *errFuncName, int lineNum, const char *format, ...);
void errSysExit                     (const char *srcFile, const char *errFuncName, int lineNum, const char *format, ...);
void debugMsg                       (const char *srcFile, const char *errFuncName, int lineNum, const char *format, ...);
void dump_process_memory_mapping    ();                                         /* read /proc/self/maps */
void dump_memory_range              (void *addr, size_t len);                   /* dump a region of memory */

/* parse_opts.h */
void parse_opts                     (int argc, char **argv);                    /* parse cmd-line options */
void usage_error                    (const char *program_name);                 /* prints usage & exit */


/* for pretty output */
#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define GREY    "\e[37m"        /* Grey */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */
#define BOLDGREY    "\e[90m"               /* Bold Grey */

#define BRIGHT      "\e[1m"
#define DIM         "\e[2m"
#define UNDERLINE   "\e[4m"
#define BLINK       "\e[5m"
#define INVERT      "\e[7m"
#define HIDDEN      "\e[8m"                 /* useful for passwords */


#endif      /* _PEACE_HELPER_HDR_H */