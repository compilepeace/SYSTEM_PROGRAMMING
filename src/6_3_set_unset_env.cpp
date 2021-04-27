/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : set_unset_env.cpp                                                 *
 *                                                                              *
 * Description: Custom implementation to setenv() and unsetenv() using getenv() *
 *              putenv() and wherever necessary modifying 'environ' itself.     *
 *                                                                              *
 ********************************************************************************/

#include <stdlib.h>     // for getenv|putenv
#include <stdio.h>      // for fprintf
#include <errno.h>      // for errno
#include <string.h>     // for strncmp, strlen

extern char **environ;      // get current process environment

int c_setenv (const char *name, const char *value, int overwrite);
int c_unsetenv (const char *name);


int main (int argc, char **argv) {

    clearenv();
    setenv ("first", "one", 0);
    c_setenv ("abhi", "thakur", 0);
    c_setenv ("abhi", "nav", 0);
    c_setenv ("abhi", "now", 0);
    system ("printenv");
    fprintf (stderr, "\nNow... unsetting abhi..\n\n");
    c_unsetenv ("abhi");
    system ("printenv");
    return 0;
}


int c_setenv (const char *name, const char *value, int overwrite) {

    char **envptr, **existing_location;
    char *add_entry;
    size_t namelen;


    /* validate input string */
    if (name == NULL || *name == '\x00' ||
        strchr (name, '=') != NULL) {
        errno = EINVAL;
        return -1;
    }

    namelen = strlen (name);
    existing_location = NULL;
    for (envptr = environ; *envptr != NULL; ++envptr) {
        // check for an already existing entry by the same 'name'
        if (strncmp (*envptr, name, namelen) == 0 && (*envptr)[namelen] == '=') {
            if (overwrite == 0) 
                return 0;
            else {
                existing_location = envptr;
                break;
            }
        }
    }

    
    // create an environment name entry string
    add_entry = (char *) malloc (namelen + strlen(value) + 2 /* for '=' and '\x00' */ );
    if (add_entry == NULL) {
        perror ("while allocating memory for environment variable");
        return -1;
    }
    sprintf (add_entry, "%s=%s", name, value);
    
    // add entry to environment list
    if (existing_location == NULL) {
        // use putenv if no entry by the same name already exists
        if (putenv (add_entry) != 0) {
            perror ("cannot add env variable using putenv");
            return -1;
        }
    }
    else    // add the entry at already existing entry @ existing_location
        *existing_location = add_entry;
    

    return 0;
}


// removes value associated with all instances of env variable 'name'
int c_unsetenv (const char *name) {

    char *dummyptr = "deleteme";
    char **envptr;
    char **ptr1;                    // stores address of first env name to be deleted
    char **ptr2;                    // stores address of last element in env list
    size_t name_len, elist_size = 0;
    bool NAME_FOUND = false;

    if (name == NULL || name[0] == '\x00') {
        errno = EINVAL;
        return -1;
    }

    name_len = strlen (name);
    for (envptr = environ; *envptr != NULL; ++envptr) {
        // store all environment names that need to be removed    
        ++elist_size;
        fprintf (stderr, "found %s\n", *envptr);
        if (strncmp(*envptr, name, name_len) == 0 && (*envptr)[name_len] == '=') {
            
            // mark all points in environment list (with dummyptr) which are to be deleted.
            // store the address of first element to be deleted
            // get the end of list by counting the number of env names (elist_size)
            if (NAME_FOUND == false) {
                ptr1 = envptr;                          // deletion will start from here
                NAME_FOUND = true;
            }
            
            *envptr = dummyptr;                         // mark position
        }
    }

fprintf (stderr, "number of env variables %ld\n", elist_size);
    if (NAME_FOUND == false) return 0;
    else {
        ptr2 = &environ[elist_size - 1];                // points to last element of env list

        while ( ptr1 < ptr2 ) {
        
            if (*ptr1 == dummyptr && *ptr2 != dummyptr) {
                // swap
                *ptr1 = *ptr2;
                *ptr2 = NULL;
                ++ptr1;
                --ptr2;
            }

            else {
                if (*ptr1 != dummyptr) {
                    ++ptr1;
                }
            
                if (*ptr2 == dummyptr) {
                    *ptr2 = NULL;
                    --ptr2;
                }
            }    
        }
        
        if (ptr1 == ptr2 && *ptr1 == dummyptr)   
            ptr1 = NULL;
    }

    return 0;
}