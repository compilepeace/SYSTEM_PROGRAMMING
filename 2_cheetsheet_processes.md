# CHEETSHEET PROCESSES, MEMORY MANAGEMENT, USERS & GROUPS
This contains my personal cheetsheet for syscalls related to processes encountered in **The Linux Programming Interface**.  


## PROCESSES
C programming environment provides 3 global symbols that represent one byte past the end of text, data and uninitialized data segment -
```
extern char etext, edata, end;  /* For example, &etext gives the address of the end of the program text / start of initialized data */

extern char **environ;          /* variable pointing to the environment list */
```
![memory_layout_of_a_process](./images/memory_layout.png) 
* The file `/proc/sys/kernel/pid_max` (2**22 for 64 bit Linux) stores one greater than the maximum PID any process can have. After this value, the kernel starts assigning PIDs again starting from 300.
* `/proc/kallsyms` provides addresses of all symbols in kernel space
* `/proc/PID/cmdline` can be used to access cmd-line arguments of any process.
* `/proc/PID/environ` contains the environment list for a process.
* pstree
* size <binary_exe>

```
#include <unistd.h>         /* for getpid */
#include <stdlib.h>         /* for getenv|putenv|setenv|unsetenv|clearenv */

#include <setjmp.h>         /* for setjmp|longjmp */
```

* pid_t **`getpid`** (void);  
~ always successfully return PID of caller process.

* pid_t **`getppid`** (void);  
~ always successfully return the PID of parent for caller process.

* char \***`getenv`** (const char *name);  
~ returns pointer to (value) string, or NULL if no such variable.

* int **`putenv`** (char *string);  
~ The *string* argument is a pointer to a string of the form "name=value". After this call, the *string* is a part of the environment (therefore, ensure that it is not an automatic variable array, i.e. should not be local to a function).  
~ returns a non-zero value on error (not -1).  

* int **`setenv`** (const char *name, const char *value, int overwrite);  
~ better than putenv (I guess).  
~ returns 0 on success, or -1 on error.

* int **`unsetenv`** (const char *name);  
~ removes environment variable *name* from environment list.  
~ returns 0 on success, or -1 on error.  

* int **`clearenv`** (void);  
~ clears the entire environement. A `#define _BSD_SOURCE` feature test macro 
~ returns 0 on success, or non-zero value on error.   
```
environ = NULL;         // this way we can clear up the environment
``` 

* int **`setjmp`** (jmp_buf env);  
~ returns 0 on initial call, nonzero (*val*) on return via longjmp().

* void **`longjmp`** (jmp_buf env, int val);  

---

## MEMORY ALLOCATION
The current limit of heap is referred to as the **`program break`**.

```
#include <unistd.h>         /* for brk|sbrk */
#include <stdlib.h>         /* for malloc|calloc|realloc|free|posix_memalign */
#include <malloc.h>         /* for memalign */

```

* int **`brk`** (void *end_data_segment);  
~ **Sets** the *program break* to the location specified by *end_data_segment*. Since virtual memory is allocated in units of pages, *end_data_segment* is effectively rounded up to the next page boundary.   
~ returns 0 on success, or -1 on error.  

* void \***`sbrk`** (intptr_t increment);  
~ **Adjusts** the *program break* by adding an *increment* to it.  
~ On success, returns the previous address of *program break*. On error, `(void *) -1` is returned.
```
sbrk(0);        // returns the current setting of program break without changing it.
```

* void \***`malloc`** (size_t size);  
~ Allocates *size* bytes from the heap and returns a (void *) pointer to the newly allocated block of memory on success, or NULL on errror. 

* void \***`calloc`** (size_t numitems, size_t size);  
~ Allocates memory for an array of identical items. The *numitems* identify how many items of *size* to allocate. Unlike malloc, it clears of the allocated memory to 0 bytes.
~ returns pointer to allocated memory on success, or NULL on error.

* void \***`realloc`** (void *ptr, size_t size);  
~ Used to *resize* a block of memory (previously allocated by one of the member functions of malloc family). The ptr argument is a pointer to the block of memory that is to be resized. The size argument specifies the desired new size of the block.  
~ Returns pointer to allocated memory on success, or NULL on error.

* void **`free`** (void *ptr);  
~ Deallocates the memory block (allocated by malloc family of functions) pointed to by *ptr*. Double-free has unpredictable results.   

* void \***`memalign`** (size_t boundary, size_t size);  
~ allocates *size* bytes starting at an address aligned to a multiple of *boundary* (which must be a power of 2).  
~ returns pointer to allocated memory on success, or NULL on error.

* int **`posix_memalign`** (void **memptr, size_t alignment, size_t size);  
~ The address of allocated memory is returned in `void *memptr` (whose address is passed in posix_memalign()). The memory is aligned to a multiple of alignment, which must be a power-of-two multiple of sizeof(void *) (4 or 8 bytes on most hardware architectures).  
~ Returns 0 on success, or a positive error number on error.  

* void \***`alloca`** (size_t size);  
~ Allocates space on *stack segment* (current function's stack frame by subtracting value from stack pointer).   
~ Returns a pointer to allocated block of memory.  

---

## USERS AND GROUPS

### The Password File: **/etc/passwd** & **/etc/shadow**  

> `abhinav:x:1000:100:Comment field for Abhinav's Account:/home/mtk:/bin/bash`  

* **Login name**: 'abhinav' is the unique name (username) which is a human-readable identifier corresponding to the UID.   
* **Encrypted password** :  The field contains a *13-character* encrypted password. If this password field contains any other string (longer than 13-chars, then it is not a valid encrypted password string and therefore the logins to this accound is disabled). If shadow-passwords are enabled, encrypted password is stored in `/etc/shadow` file (see `shadow(5)` manual page for details) and this field contains the char 'x' or nothing (an empty field means no password is required to login to this account).  
* **UID**: If user ID field stores a 0, this account has superuser privileges.  
* **GID**: Group ID of first of the groups to which user is the member. Further group membership information is stored in system groups file.  
* **Comment**: This field stores text about the user.  
* **Home directory**: stores the path to initial directory into which the user is placed after loging in.
* **Login shell**: This stores path of program to which control is transferred once the user is logged in.  

### The Group File: **/etc/group** & **/etc/gshadow**
For controlling access to files and system resources, it is useful to organize users into groups. The `/etc/group` file lists extra group membership for each user.  

> `hostel_room_158:x:106:compilepeace,gaurav,saurabh,biki`

* **Group Name**: symbolic representation of GID (similar to username).
* **Encrypted Password**: If shadowing is enabled, this field contains an 'x' and encrypted password is stored in shadow group file `/etc/gshadow` (which can only be accessed by privileged programs).
* **GID**: numeric ID for this group. A GID of 0 means the group has root privileges. 
* **User list**: comma-separated list of usernames who are members of this group.  
```
To record that the user avr is a member of the groups users, staff, and teach, we
would see the following record in the password file:
    avr:x:1001:100:Anthony Robins:/home/avr:/bin/bash

And the following records would appear in the group file:
    users:x:100:
    staff:x:101:mtk,avr,martinl
    teach:x:104:avr,rlb,alc
```

