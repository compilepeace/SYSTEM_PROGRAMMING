/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : custom_getpwnam.cpp                                               *
 *                                                                              *
 * Description: Custom implementation of getpwnam() using getpwent(),           *
 *              setpwent() and endpwent()                                       *
 *                                                                              *
 * NOTE: Compile and link with peace_helper.o -                                 *
 *          gcc custom_getpwnam.cpp peace_helper.cpp -o ./exe                   *
 *                                                                              *
 ********************************************************************************/



  
#include <pwd.h>            /* for getpwent|setpwent|endpwent */
#include "peace_helper.h"   /* for error handling & debugging */

#define DEBUG_INFO  __FILE__,__FUNCTION__,__LINE__
#define MAX_LEN_LOGIN_NAME  sysconf(_SC_LOGIN_NAME_MAX)

struct passwd *custom_getpwnam (const char *name);

int main () {
    struct passwd *pwent;

    pwent = custom_getpwnam ("csfsjlg");
    if (pwent != NULL) {
        fprintf (   stderr,
                    "login name: %s\n"
                    "encrypted password: %s\n"
                    "UID: %d\n"
                    "GID: %d\n"
                    "comment: %s\n"
                    "home dir: %s\n"
                    "user shell: %s\n",
                    pwent->pw_name,
                    pwent->pw_passwd,
                    pwent->pw_uid,
                    pwent->pw_gid,
                    pwent->pw_gecos,
                    pwent->pw_dir,
                    pwent->pw_shell);
    }

    return 0;
}

struct passwd *custom_getpwnam (const char *name) {
    
    struct passwd *pwent;
    int saved_errno;

    saved_errno = errno;

    /* name validation is done via strncmp() */
    while ((pwent = getpwent()) != NULL) {
        if (strncmp (name, pwent->pw_name, MAX_LEN_LOGIN_NAME) == 0 &&
            name[strlen(name)] == '\x00') {
                debugMsg (DEBUG_INFO, "Found /etc/passwd entry for: %s", pwent->pw_name);
                break;
        }
    }

    if (pwent == NULL && errno != saved_errno) {
        errSysMsg (DEBUG_INFO, "getpwent()");
        return NULL;
    }

    endpwent ();
    return pwent;
}