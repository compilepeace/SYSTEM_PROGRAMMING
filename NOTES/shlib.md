# SHLIB 
**Linking** (the process of combining one or more objects) involves **symbol relocation** (resolving code/data references in one objects to definitions in another object) which occurs at 2 times in a program's life: 

- Compile-time (`man ld`)
- Run-time (`man ld.so`)

**NOTE**: Static libraries are *archives* (i.e. a bundle) of compile object files built using **ar** (`man ar`). Static linker `ld` determines which object files from archive to copy into the final executable.

```
BUILDING STATICALLY/DYNAMICALLY LINKED EXECUTABLES

$ cc -static ./peace.c -o speace    # statically linked executable
$ cc ./peace.c -o dpeace            # dynamically linked (by default)
```

## Building Statically linked executables
* Compile (using `cc -c`) all source files into object files. (no need to use `cc -fPIC` option to compile object files)
* Use `-static` link-time option to generate statically linked executable output.
```
LINK TO glibc-static PACKAGE
$ cc -g -static -o smain  main.c    # executable statically link to glibc-static package

LINK TO VARIOUS OBJECT FILES 
$ cc -g -c bar.c        
$ cc -g -static -o smain  main.c bar.o    # statically link main to 'bar.o' and all its dependencies
```

## Creating and Using Shared Libraries (P842 TLPI)
These are the steps - 
* Compile source code into PIC object code (using `-c -fPIC`)
* Create a shared library combining all PIC object code files (using `-shared`).
* Link (via static-linker `ld`) main program (`main.c`) against created shared library (`libfoo.so`).
```
$ cc -g -Wall -c -fPIC        mod1.c mod2.c mod3.c
$ cc -g -shared -o libfoo.so  mod1.o mod2.o mod3.o  # using real-name for DSO creation 
$ cc -g -Wall -o main         main.c libfoo.so
``` 
If **DT_SONAME** tag is present in .dynamic section of any executable, the dynamic linker will search for the library by its soname instead. In order to create `soname` (an alias name for shared library that will be embedded into the final `main` executable), pass on `-soname` flag to the static-linker(ld) (`-Wl,<ld_flag_here>`) while creating `-shared` library.
```
COMPILING SHARED LIBRARY (using SONAME)
$ cc -g -Wall -c fPIC   mod1.c mod2.c mod3.c
$ cc -g -shared -Wl,-soname,libfoo.so.1 -o libfoo.so.1.2    mod1.o mod2.o mod3.o 
$ ln -s libfoo.so.1.2 libfoo.so.1       # soname that will be searched for by dynamic linker
$ ln -s libfoo.so.1 libfoo.so           # linker-name (for static-linker to be able to interpret -lfoo) 

STATICALLY LINKING main.c AGAINST libfoo.so (using ld)
$ cc -g -Wall -o main       main.c -L. -lfoo
``` 
* `-L.` specifies to `ld` to search for `-lfoo` (i.e. libfoo.so or libfoo.a) in current directory (along with the standard search path).

**NOTE**: `ldconfig(8)` automates updating of soname links (to real DSO filenames). Apart from that, both `soname` and `linker-name` allows us to perform **verison-independent** (on latest versions) operations on DSOs. 

### **Verifying** 
Using `ldd` or `objdump -p` or `readelf -d` to confirm the shared library is liked against main (final) program (as `DT_NEEDED` entry in .dynamic section of ELF binary).
Only `ldd` among them shows the dependency of an executable transitively by making dynamic linker to **load** dependencies.
```
IDENTIFY DEPENDENCIES
$ ldd ./main                            # list entire dependency tree  
$ objdump -p /path/to/main | grep "NEEDED" 
$ readelf -d /path/to/main | grep "NEEDED"

$ pldd <pid>    # list DSO (dynamic shared objects) loaded by a process

VERIFY SONAME (libxxx.so.major.minor.patch)
$ objdump -p /path/to/dso | grep "SONAME"
$ readelf -d /path/to/dso | grep "SONAME"
```

### **Running Program**
Running a `dynamically linked` by dynamic linker involves -

1. **Identifying** what DSO's are needed by the target executable. Dependencies are identified by reading `.dynamic` section and identifying all entries tagged as `DT_NEEDED`. 
2. **Finding** required (DT_NEEDED) libraries at various *search paths* in a *predefined search order*. 
3. **Loading** libraries (*load-order* and *symbol-visibility* matters during *symbol resolution*). 

So, the dynamic linker handles loading DSO's  - 
* [load time] DT_NEEDED 
* [load time] Transitive dependencies
* [Runtime] loading additional DSO dependencies (using `dlopen()` libld.so API).


Running a program that links against custom library (`libfoo.so`) not present inside standard locations (eg: `/usr/lib64` or `/lib64`) can be done via one of the methods.

* Using **LD_LIBRARY_PATH** (`$ LD_LIBRARY_PATH=./path/to/so/ main`)
*  

## **ldconfig**
Responsible for - 
* updating `/etc/ld.so.cache` (used by dynamic linker as a table storing all the pathnames to be searched for loading a DSO).
* updating the *soname symlinks*.
