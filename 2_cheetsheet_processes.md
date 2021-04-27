# CHEETSHEET PROCESSES
This contains my personal cheetsheet for syscalls related to processes encountered in **The Linux Programming Interface**.  


## Processes
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

