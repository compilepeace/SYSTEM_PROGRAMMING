/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : custom_readv_writev.cpp                                           *
 *                                                                              *
 * Description: Custom implementation of readv() and writev to be done.         *
 *              Currently only implementations of readv() & writev() are  made. *
 *                                                                              *
 * NOTE: Compile and link with peace_helper.o -                                 *
 *          gcc custom_readv_writev.cpp peace_helper.cpp -o ./exe               *
 *                                                                              *
 ********************************************************************************/

#include <sys/uio.h>
#include "peace_helper.h"

#define DEUBUG_INFO __FILE__,__FUNCTION__,__LINE__

/*
struct iovec {
    void *iov_base;	    // Pointer to data. 
    size_t iov_len;	    // Length of data.  
};
*/

int main () {
    struct iovec iov[3];
    int fd, marks = 0x42;
    char msg[8] = {'a','b','h','i','n','a','v','\x00'};
    char ch = 'A';
    size_t retValue = 0, totalBytes = 0;

    /* Exclusively (O_EXCL) open a file for writing */
    fd = open ("temp.out", O_CREAT|O_EXCL|O_WRONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fd == -1) 
        errSysExit (DEUBUG_INFO, "open failed");

    /* setup iov[] for writev() syscall */
    iov[0].iov_base = msg;
    iov[0].iov_len  = strlen(msg);
    totalBytes += iov[0].iov_len;

    iov[1].iov_base = &marks;
    iov[1].iov_len  = sizeof (int);
    totalBytes += iov[1].iov_len;

    iov[2].iov_base = &ch;
    iov[2].iov_len  = sizeof (char);
    totalBytes += iov[2].iov_len;

    /* perform multiple buffer write(gather output) via writev() syscall */
    if ( (retValue = writev (fd, iov, 3)) != totalBytes) {
        if (retValue == -1)
            errSysExit (DEUBUG_INFO, "writev()");
        else
            errUsrMsg (DEUBUG_INFO, "writev(): Insufficient bytes written by writev()");
    }

    /* release open resources */
    if (close(fd) == -1) 
        errSysExit (DEUBUG_INFO, "while closing temp.out");


    /* open temp.out (file just created above) for reading */
    fd = open ("temp.out", O_CREAT| O_RDONLY, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    if (fd == -1) 
        errSysExit (DEUBUG_INFO, "open failed");

    /* Now, use readv() to read multiple buffers from fd */
    int new_marks;
    char new_msg[9] = {};
    char new_ch;
    struct iovec new_iov[3];
    totalBytes = 0;

    /* setup iov[] for readv() syscall */
    new_iov[0].iov_base = new_msg;
    new_iov[0].iov_len  = 7;
    totalBytes += new_iov[0].iov_len;

    new_iov[1].iov_base = &new_marks;
    new_iov[1].iov_len  = sizeof (int);
    totalBytes += new_iov[1].iov_len;

    new_iov[2].iov_base = &new_ch;
    new_iov[2].iov_len  = sizeof (char);
    totalBytes += new_iov[2].iov_len;

    /* perform multiple buffer read(scatter input) via readv() syscall */
    if ((retValue = readv (fd, new_iov, 3)) != totalBytes) {
        fprintf (stderr, "total_bytes read %d: %d: %d\n", retValue, totalBytes, errno);
        if (retValue == -1)
            errSysExit (DEUBUG_INFO, "readv()");
        else
            errSysExit (DEUBUG_INFO, "readv(): Insufficient bytes read from file");
    }

    /* verify read data */
    debugMsg (DEUBUG_INFO, "read data (new_msg: %s | new_marks: %d | new_ch: %c)",
                            new_msg, new_marks, new_ch);

    /* release open resources */
    if (close(fd) == -1) 
        errSysExit (DEUBUG_INFO, "while closing temp.out");

    return 0;
}