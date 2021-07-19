# GDB CHEETSHEET	

##  **Compile & Load in gdb**
```
$ gcc fibber.c -o fibber_bin

$ gdb --quiet ./fibber_bin			# -q flag (no welcome msg)
Reading symbols from ./fibber_bin...
(No debugging symbols found in ./fibber_bin)
(gdb) 

$ gdb -q
(gdb) file ./fibber_bin 			# load binary inside gdb	
Reading symbols from ./fibber_bin...
(gdb) quit
```

## **Running & Starting a program**
```
$ gdb ./fibber_bin -q
(gdb) r AAAA				# runs 
(gdb) start	AAAA			# runs & breaks @ main()
(gdb) c						# continue program execution 
(gdb) r < <(cat xx.txt)		# provides stdin to program
```
* gdb documentation for [run/start]
* gdb documentation for [continue]

[run/start]: https://sourceware.org/gdb/current/onlinedocs/gdb/Starting.html#Starting
[continue]: https://sourceware.org/gdb/current/onlinedocs/gdb/Continuing-and-Stepping.html#Continuing-and-Stepping


## **Code Breakpoints** (listing, setting, deleting) 
```
(gdb) break *0x55555555184	# set breakpoint @ <address>
(gdb) b main				# set breakpoint @ function symbol

(gdb) info breakpoints		# list all breakpoints
(gdb) i b	

(gdb) clear fibbonacci		# delete breakpoint @ symbol
(gdb) clear *0x55555555184	# delete breakpoint @ <address>
(gdb) d 2					# delete 2nd entry in breakpoint table
(gdb) d						# delete all breakpoints

(gdb) disable 2				# disabling breakpoint number 2
(gdb) enable 2				# enabling breakpoint number 2

CONDITIONAL BREAKPOINTS
(gdb) condition 1 $eax != 0			# set a condition to breakpoint 1						
(gdb) condition 2 counter == 5		# set a condition to breakpoint 2
```

##  **Data Access Breakpoints**  (Watchpoints/Hardware breakpoints)
There are **4** dedicated Intel special purpose **debug registers**. These registers inform the **MMU** (memory management unit) that it should watch for **read**, **write**, **execute**, or **IO accesses** targeted the specified addresses/IO ports Watchpoints are used to set hardware breakpoints to break when an access is performed on the specified address, i.e. setting **Break-on-Read** vs. **Break-on-Write**. Further, `hbreak` is used to set hardware breakpoints which ensures **Break-On-Execute**.
```
(gdb) watch var1				# break on Write-Only access
(gdb) rwatch <address>			# break on Read-Only access
(gdb) awatch <address> 			# break on Read-Write access

(gdb) watch *(char *) <address>			# <label1>	
(gdb) watch *(long long *) <address> 	# <label2>

(gdb) hbreak <address>			# similar to break <address>
(gdb) hb *0x00005555555551ad 	# short for hbreak
```

`<label1>` sets a watchpoint to break on access to one byte @ `<address>` and therefore wouldn't fire if `<address+2>` was written to. whereas,   
`<label2>` would fire a breakpoint if any of the 8 bytes starting @ `<address>` were written to.

* gdb documentation for [deleting breakpoints].
* gdb documentation for [watchpoints]
* gdb documentation for [disabling and enabling breakpoints]
* gdb documentation for [hbreak].

[deleting breakpoints]: https://sourceware.org/gdb/current/onlinedocs/gdb/Delete-Breaks.html#Delete-Breaks
[watchpoints]: https://sourceware.org/gdb/current/onlinedocs/gdb/Set-Watchpoints.html
[disabling and enabling breakpoints]: https://sourceware.org/gdb/current/onlinedocs/gdb/Disabling.html
[hbreak]: https://sourceware.org/gdb/current/onlinedocs/gdb/Set-Breaks.html#Set-Breaks

## **Disassemble**
Bytes can be disassembled by specifying either of - **function symbol** or **address/offset** location to *disassemble* (*disass*) command in gdb.
```
(gdb) disassemble main		# disassemble main function symbol
(gdb) disass 0x1184			
(gdb) disass /r main		# display raw instruction bytes too !

(gdb) x/10i 0x11c1			# examine 10 instructions @ <address/offset> 

(gdb) display/3i $rip		# everytime the program stops, gdb displays 3 instructions @ RIP.
(gdb) display/8xg $rsp		# setting up updated stack view
```
* gdb documentation for [disassemble]

[disassemble]: https://sourceware.org/gdb/current/onlinedocs/gdb/Machine-Code.html


## **Examining/Modifying Registers & Memory**
```
(gdb) info registers	# view GPR (general purpose registers)
(gdb) i r a				# view all registers
(gdb) i r rax rbx 		# view rax and rbx

(gdb) print/x $rax		# print $rax in hexadecimal format
(gdb) p/u $rax			# print $rax in unsigned int format
(gdb) p/d $rax			# print $rax in signed decimal format
(gdb) p/o $rax			# print $rax in octal format

(gdb) set $var = 777					# dummy variable
(gdb) set $rax = 0xdeadbeefcafebabe		# rax = <value>
(gdb) set {short}$rsp = 0xFFFF			# *rsp = 0xffff
(gdb) set {long long}$rsp = 0x1337bee7	# *rsp = <value>

(gdb) x/10xb $rsp
(gdb) x/10xh $rsp
(gdb) x/10xw $rsp
(gdb) x/-10xg $rsp		# examine 10xg towards lower memory address	
```
* gdb documentation for [registers]
* gdb documentation for [examine memory]

[examine memory]: https://sourceware.org/gdb/current/onlinedocs/gdb/Memory.html#index-examining-memory

[registers]: https://sourceware.org/gdb/onlinedocs/gdb/Registers.html 

## **Misc**
## **Backtracing function calls** (Stacktrace)
```
STEPPING OVER|INTO|OUT
(gdb) ni			# 'nexti' for step over call instructions
(gdb) si 			# 'stepi' for step into call instructions
(gdb) fin			# 'finish' to step out of current function context

STACKTRACE INFO
(gdb) info frame	# current stack frame info
(gdb) bt			# backtrace function calls
#0  0x0000555555555169 in fibbonacci ()
#1  0x00005555555551e5 in main ()

RUN UNTIL ADDRESS
(gdb) u *0x5555555551dc  	# run until <address> (temporary breakpoint)

# SET ASSEMBLY SYNTAX
(gdb) set disassembly-flavor intel
(gdb) set disassembly-flavor att


```
* gdb documentation for [backtraces]
* gdb documentation for [stepping]

[backtraces]: https://sourceware.org/gdb/current/onlinedocs/gdb/Backtrace.html#Backtrace 

[stepping]: https://sourceware.org/gdb/current/onlinedocs/gdb/Backtrace.html#Backtrace


## **Attaching to running processes** 
```
$ echo 0 | sudo tee /proc/sys/kernel/yama/ptrace_scope		# to derestrict ptrace access

$ echo 1 | sudo tee /proc/sys/kernel/yama/ptrace_scope		# to restrict ptrace access again

$ sudo gdb -q
(gdb) attach <PID>			# to attach to PID process in gdb
```

## **GDB configuration file**
Same set of commands can be executed everytime gdb is fired up by using **configuration scripts**, i.e. firing up gdb with a `-x` option.

```
$ cat ./gdbconfigfile		# recommended starting commands
display/10i $rip
display/x $rbp
display/x $rsp
display/x $rax
display/x $rbx
display/x $rcx
display/x $rdx
display/x $rdi
display/x $rsi
display/x $r8
display/x $r9
display/x $r12
display/x $r13
display/x $r14
display/10gx $rsp
start
$ gdb -q ./exe -x ./gdbconfigfile		# startup commands for exe
(gdb) 
```

* [kernel hardening] in Ubuntu

[kernel hardening]: https://wiki.ubuntu.com/SecurityTeam/Roadmap/KernelHardening#ptrace%20Protection


## **GDB - TUI (Text user interface)**

```
ctrl-x-a						# move from text mode to tui mode
ctrl-x-1						# show source
ctrl-x-2						# show regs
ctrl-l							# To reconstruct any j
layout asm						# initialize asm-source windows
layout regs						# initialize register window  
tui regs float					# To have FPU's view rather than general purpose regs
tui regs general				# To have general purpose regs view in reg windows
ctrl-p							# To go to previous commands (while in tui mode) 
```
---

##	SOURCE CODE DEBUGGING
```
(gdb) list					# Lists the source code typically from where the main function starts
							# it is useless if you don't have the source code because gdb itself
							# haves a look at the source_code.c file in the directory to list 
							# source code.
(gdb) list 1, 50				# Lists source code from line number 1 to line number 50
(gdb) info functions			# Lists all the local functions added as a part of debug symbols (-g
							# flag) separately. If debug symbols are not present then local names
							# of functions will be present but they will be present in "Non-debuging
							# symbols:" section.
(gdb) info sources			# To list all the source code files(only for debug symbols added file)

@@	For global and static variables
	>	info variables 					# Prints only 'global' and 'static' variables (not local)
@@	For local variables constituents
	> 	info locals						# Prints local variables in the current stack frame
	>	info scope 						# Press TAB to list all the scopes
	> 	info scope func_name			# lists all variable details in function scopes

(gdb) maint print symbols file_to_store	# dump the symbols into a separate file
```

##	SRIPPING SYMBOLS OFF A BINARY
```	
$ objcopy --only-keep-debug ./bin_dbgsyms dbgsyms
$ strip --strip-all ./bin
```

##	STRIPPING SYMBOLS OFF A BINARY
```		
$	strip --strip-debug --strip-unneeded binary_to_strip
=>	This command removes debugging symbols off any binary_file (w/o --strip-unneeded flag).
	With --strip-unneeded flag, it remove everything apart from what the binary must have
	to load and work properly (try 'info variables' with it, you'll notice that the global
	and static variable names are also removed).
```

##	ADDING DEBUG SYMBOLS
```
>	symbol-file debug_symbols_filename		# gdb reads debug symbols from a file manually.
											# Loads the symbol file into gdb	
$	objcopy --add-gnu-debuglink=debug_symbols_filename stripped_binary	(into which you want to
																		 add debug symbols)
```

##	INSPECTING SYMBOLS NM
'nm' lists symbols from object files.

```
	$ nm -n ./binary_file					# -n flag to get sorted order o/p with respect to address
											# Use -S flag to get 'size' info about symbols
	08049f18 	 d 		 __CTOR_END__										
	08048474	 T 		 AddNumbers			# specifies that AddNumbers is at 0804874 virtual address
											# of Text section.
	.
	.
	.
	Virtual		Symbol 		Symbol
	Address		type 		Name
		 
->	Lowercase is local symbol
->	Uppercase is External

- A 	: 	Absolute symbol
- B 	:	In the uninitialised data section (.bss)
- D 	: 	In the initialised data section (.data)
- N 	: 	Debugging symbol
- T 	:	In the text section (.text)
- U 	: 	Symbol undefined right now
```

##	STRACE
Trace all System calls made by the program executable, i.e. it makes te syscall monitoring happen. With strace, we can also run interpreted language scripts like script.py 

```
$ strace -e read,write,mmap ./executable args
			- "-o" output_file
			- "-t" timestamp
			- "-r" relative timestamp


	$ strace -e write,read,exit,open,connect,socket ./binary args		# To filter out only a list
																			# of syscalls
	$ strace nc google.com 80		# example
	$ sudo strace -p process_id		# Attaching strace to a running process
	$ strace -c program_name		# prints various statistics of syscalls		
```

##	GDB's CONVENIENCE VARIABLES
```
>	set $var = 10					# creates a convenience variable storing 10
>	set argv[1] = "AAA"				# manipulating argv[1]
> 	set $dyn = (char *)malloc(10)	# dynamically allocates memory to var 'dyn'
> 	call strcpy($dyn, $argv[1])		# calling library function on convenience variables.
									# we can call functions in binary and those linked with
									# it.			
> 	call Addnumbers($var, 20)		# we can also call any function in scope
									# and use convenience variables in it.
```

##	DOWNLOAD AND INSTALL QEMU
```
		$ apt-get build-dep qemu
		$ wget http://wiki.qemu.org/download/qemu-1.2.0.tar.bz2
		$ /.configure --target-list=arm-softmmu	
		$ make
		$ make install
```

##	DOWNLOAD DEBIAN AND ARMEL IMAGES
Can download from debian website or -
```
		$ http://people.debian.org/~aurel32/qemu/armel/

		$ launchVM.sh
		$ apt-get update; apt-get install ssh , gcc and gdb
```

##	GDB MESSING UP WITH STACK ADDRESSES
Use these 2 commands bellow to be close to normal program's memory layout.
```
(gdb) unset environment LINES
(gdb) unset environment COLUMNS  	# You still have to take care of '_' variable 
```						