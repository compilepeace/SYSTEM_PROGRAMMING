/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : 12_0_uname.cpp                                                         *
 *                                                                              *
 * Description: Retrieving system information using uname() syscall.            *
 *                                                                              *
 * NOTE: Compile and link with peace_helper.o -                                 *
 *          gcc 12_0_uname.cpp peace_helper.cpp -o ./exe                   *
 *                                                                              *
 ********************************************************************************/

#include <sys/utsname.h>            /* uname() syscall */
#include "peace_helper.h"           /* helper functions */

#define DEBUG_INFO __FUNCTION__,__FILE__,__LINE__


int main () {
    struct utsname sysinfo;

    if (uname (&sysinfo) == -1)
        errSysExit (DEBUG_INFO, "uname()");
    
    fprintf (stderr, 
                "sysname       : %s\n"
                "nodename      : %s\n"
                "release       : %s\n"
                "version       : %s\n"
                "machine       : %s\n"
                "domainname    : %s\n",
                sysinfo.sysname, sysinfo.nodename, 
                sysinfo.release, sysinfo.version,
                sysinfo.machine, sysinfo.domainname);
}