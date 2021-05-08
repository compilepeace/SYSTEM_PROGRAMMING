/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : peace_helper.cpp                                                  *
 *                                                                              *
 * Description: A module containing some helper functions for the ease of       *
 *              development & debugging. These include                          *
 *                                                                              *
 * > Error Handling                                                             *
 * > Dump memory mapping of the process                                         *
 * > Hexdump process memory regions                                             *
 *                                                                              *
 ********************************************************************************/


#include <stdarg.h>         /* declarations for ellipsis (...) for variable arguments */
#include "peace_helper.h"

/* MACRO definitions */
#define DEBUG_INFO  __FILE__,__FUNCTION__,__LINE__
#define BLOCK_SIZE      0x200
#define MAX_BUFFER_SIZE 0x200

/* Function Prototypes */
void terminate (Boolean use_exit_syscall);
void write_msg (const char *format, va_list argList, Boolean success, int fd,
                const char *sourceFile, const char *errFuncName, int lineNum);

int logfd = -1;

/*
 * Sets beautification on the basis of 'fd' whereas writes error or debug messages
 * (based on 'success' parameter) to 'fd'.
 * 
 * If 'success' is TRUE;  write user message alone to file descriptor 'fd'.
 * If 'success' is FALSE; write user message along with system error msg to 'fd'.
 *  
 * If file descriptor 'fd' is either of STDOUT or STDERR, write a beautified
 * msg to 'fd'; otherwise write the message in raw ASCII form to 'fd'.
 * 
 * If (errNum < 0), errno descriptions are not written along with user-passed
 * error message. Otherwise, both 'errno descriptions' and 'userMsg' are
 * written to 'fd'.
 * 
 */ 
void write_msg (const char *format, va_list argList, int fd, Boolean success, int errNum,
                const char *srcFile, const char *errFuncName, int lineNum) {

    char userMsg[MAX_BUFFER_SIZE], sysErrMsg[MAX_BUFFER_SIZE], errStr[3 * MAX_BUFFER_SIZE];

    vsnprintf (userMsg, MAX_BUFFER_SIZE, format, argList);       /* user msg created */    
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
        /* create beautified msg string */
        if (success == TRUE){
            /* write debug msg */
            dprintf (fd, BOLDGREEN"[+]" BLUE " %s\n" RESET, userMsg);
        }
        else {
            /* write error */
            dprintf (fd, 
                    BOLDRED "[-]" RESET " (%s, %s, %d)" BLUE " %s" CYAN " [%s]\n" RESET,
                    srcFile, errFuncName, lineNum, 
                    (errNum > 0) ? strerror(errNum): "an error occured",
                    userMsg);
        }       
    }
    else {
        /* create raw ASCII string to be logged into LOGFILE */
        if (success == TRUE){
            /* write debug msg */
            dprintf (fd, "[+] %s\n", userMsg);
        }  
        else {
            /* write error */
            dprintf (fd, 
                    "[-] (%s, %s, %d) %s [%s]\n", 
                    srcFile, errFuncName, lineNum, 
                    (errNum > 0) ? strerror(errNum): "an error occured",
                    userMsg);
        }
    }
}


/* 
 * Simply writes user-supplied error message to either of STDERR_FILENO or file
 * represented by logfd (if logging is enabled); without including string description
 * representing errno.
 */
void errUsrMsg (const char *srcFile, const char *errFuncName, int lineNum, const char *format, ...) {
    va_list argList;
    int fd;

    /* set write fd to appropriate value by checking if --log=[filename] (error logging is enabled) */
    if (logfd == -1)    fd = STDERR_FILENO;
    else                fd = logfd;

    va_start (argList, format);
    write_msg (format, argList, fd, FALSE, -1, srcFile, errFuncName, lineNum);
    va_end (argList);
}


/* 
 * Same as errMsg() except that it writes 'error description' represented by errno along with
 * user-supplied error message to either of STDERR_FILENO or logfd.
 */
void errSysMsg (const char *srcFile, const char *errFuncName, int lineNum, const char *format, ...) {
    va_list argList;
    int fd;

    /* set write fd to appropriate value by checking if --log=[filename] (error logging is enabled) */
    if (logfd == -1)    fd = STDERR_FILENO;
    else                fd = logfd;

    va_start (argList, format);
    write_msg (format, argList, fd, FALSE, errno, srcFile, errFuncName, lineNum);
    va_end (argList);
}


/* 
 * Same as errSysMsg() except that it terminates via exit or _exit after writing error.
 */
void errSysExit (const char *srcFile, const char *errFuncName, int lineNum, const char *format, ...) {
    va_list argList;
    int fd;

    /* set write fd to appropriate value by checking if --log=[filename] (error logging is enabled) */
    if (logfd == -1)    fd = STDERR_FILENO;
    else                fd = logfd;

    va_start (argList, format);
    write_msg (format, argList, fd, FALSE, errno, srcFile, errFuncName, lineNum);
    va_end (argList);

    terminate (TRUE);
}


/* 
 * Same as errSysMsg() except that it terminates via exit or _exit after writing error.
 */
void debugMsg (const char *srcFile, const char *errFuncName, int lineNum, const char *format, ...) {
    va_list argList;
    int fd;

    /* set write fd to appropriate value by checking if --log=[filename] (error logging is enabled) */
    if (logfd == -1)    fd = STDERR_FILENO;
    else                fd = logfd;

    va_start (argList, format);
    write_msg (format, argList, fd, TRUE, -1, srcFile, errFuncName, lineNum);
    va_end (argList);
}


/* 
 * Call abort() (causing a core dump) if 'CP_COREDUMP' environment variable is defined and is not 
 * set to a NULL value. Otherwise call exit() or _exit() depending on what value is passed
 * in use_exit_syscall parameter.
 */
void terminate (Boolean use_exit_syscall) {
    char *estr;

    /* check if CP_COREDUMP is set to a non-null value */
    estr = getenv ("CP_COREDUMP");

    if (estr != NULL && estr[0] != '\x00')
        abort ();
    else if (use_exit_syscall)
        _exit (EXIT_FAILURE);
    else
        exit (EXIT_FAILURE);
}


/* 
 * Dumps the process address space to STDERR via /proc/self/maps 
 */
void dump_process_memory_mapping () {
    char procmem;
    
    int pfd = open ("/proc/self/maps", O_RDONLY);
    if (pfd == -1) {
        errSysMsg (DEBUG_INFO, "while opening /proc/self/maps\n");
        return;
    }

    while (read (pfd, &procmem, 1) != 0) {
        fprintf (stderr, "%c", procmem);
    }
    fprintf (stderr, "\n");
} 


/* 
 * dump a range of memory : [addr, addr + len) 
 */ 
void dump_memory_range (void *addr, size_t len){    
    /* Used for debugging: Prints the hexdump memory mapping of [addr, addr+len] */
    int lcount = 0;
    uint8_t *ptr = (uint8_t *)addr; 
    unsigned int offset = 0;

    fprintf (stderr, "\n-x-x-x-x-x- " BOLDRED "DEBUGGING MODE (Hexdump Rocks)" RESET " -x-x-x-x-x-\n");
    fprintf (stderr, BLUE "\n%08x: " RESET, offset);
    
    // print padding
    size_t dspace = 16 - ((len % 16) ? (len % 16): 0);
    size_t sspace = dspace/4;
    size_t padding = (dspace * 2) + sspace;
    for (size_t i = 0; i < len; ++i){
        ++lcount;
        ++offset;

        // print the hex representation of byte pointed to by *ptr
        fprintf (stderr, GREEN "%02x" RESET, (*ptr & 0xff));
        ++ptr;

        if (!(lcount % 4))
            fprintf (stderr, " ");

        if (!(lcount % 16) or (i == len-1)){
            // print padding before printing ASCII repr
            if (i == len-1 and (lcount % 16)){
                while (padding--) 
                    fprintf(stderr, " ");
            }        

            // print the corresponding ASCII representation of byte pointed to by *ptr
            fprintf (stderr, "\t | ");
            for (uint8_t *start = (ptr - 16); start != ptr; ++start){
                if (*start >= 0x21 and *start <= 0x7e){
                    // printable range
                    fprintf (stderr, YELLOW "%c" RESET, *start);
                }
                else{
                    // Non-printable range
                    fprintf (stderr, RED "." RED);
                }
            }
            fprintf (stderr, BLUE "\n%08x: " RESET, offset);
            lcount = 0;
        }
    }
    fprintf (stderr, "\n\n");
}