# WINDBG CHEETSHEET
Everything we input is treated as Hexadecimal by default.

## **Breakpoints** (b*)
Both Code and Data Access (hardware) Breakpoints.
```
> bp <address/symname>	# set a breakpoint
> bl					# list breakpoints
> bc <number> 			# breakpoint clear (number given by bl)
> bd <number>			# breakpoint disable
> be <number> 			# breakpoint enable
> bp $exentry			# break @ entry point of binary, i.e. within C Runtime
```

### Hardware Breakpoints
`ba <access type> <data size> <address>`
```
> ba w 4 00000000`0014fdf4		# break when this location gets written
> ba r 4 00000000`0014fdf4		# break when this location gets read or written to
> ba e 1 00000001`40001050		# break when this location gets executed
```

### Temporary Code Breakpoints
`pa <address or symbol>` will print out every instruction it **steps over** on its way to address. (ste**p** to **a**ddress)  
`ta <address or symbol>` will print out every instruction it **steps into** on its way to address. (**t**race to **a**ddress)  
`One-shot breakpoint` (bp **/1**) will get deleted after it gets triggered once.
```
> pa 00000001`40001050			
> ta 00000001`40001050
> bp /1 00000001`40001050		# create a one-shot breakpoint
```
* ba stands for **b**reak-on-**a**ccess
* Microsoft documentation for [breakpoints]
* Microsoft documentation for [break-on-access]

[breakpoints]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/bp--bu--bm--set-breakpoint-
[break-on-access]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/ba--break-on-access-


## **Running** (g)
```
> .reload /f	# reload all modules
> g				# run the program, short for go
> .restart		# similar to gdb's r
```
* Microsoft documentation for [go]


[go]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/g--go-


## **Registers** (r)
```
> r							# view all registers
> r rax, rbx, rcx			# view selected registers
> r ax = 0xdead, bl = 0x10	# modify registers
```

## **Memory** (d*)
Examining memory, d* (**d**isplay) form of instructions.
```
d[bdqa] <address> L<number>

> db rsp L6				# display 6 bytes @ rsp
> dd rsp L6				# display 6 double-words @ rsp
> da 00000001`40002220	# display ASCII string @ address

> dd poi(rsp)			# displya a double-word @ *[rsp], poi() is used for dereferencing memory addresses.
```
Modifying memory, e* (**e**nter values) form of instructions.
```
> eb rsp 11 22 33 44	# enter bytes @ rsp
> db rsp L4
> ed rsp 0xdeadbeef
> db rsp L1
```

* Microsoft documentation for [e*] instructions.
* Microsoft documentation for [address range syntax].
* Microsoft documentation for [viewing and editing memory].

[e*]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/e--ea--eb--ed--ed--ef--ep--eq--eu--ew--eza--ezu--enter-values-
[address range syntax]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/address-and-address-range-syntax
[viewing and editing memory]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/memory-window


## **Stepping Over|In|Out**
```
> p			# step over (equivalent to 'ni' in gdb)
> p 5		# step over 5 instructions

> t			# step into (equivalent to 'si' in gdb)
> t 5		# step into 5 instructions

> gu		# go up, i.e. step out (equivalent to 'finish' in gdb)
```
* Microsoft documentation for [p]
* Microsoft documentation for [t]
* Microsoft documentation for [gu]
* Microsoft documentation for [Controlling the target]

[p]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/p--step-
[t]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/t--trace-
[gu]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/gu--go-up-
[Controlling the target]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/controlling-the-target
## **Stack Backtrace**
```
> k			# get a stack backtrace 
```
* Microsoft documentation for vewing the [call stack]
* Microsoft documentation for [k command].

[call stack]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/calls-window
[k command]: https://docs.microsoft.com/en-us/windows-hardware/drivers/debugger/k--kb--kc--kd--kp--kp--kv--display-stack-backtrace-


---

## OST 1 

```
# windbg -QY sample.exe args 		# Tells windgb to save the layout while creating

> g 		# run
> gu		# step-out of function

> bp basic_vuln!main    # set a breakpoint for main() in basic_vuln process.
> bu basic_vuln!main	# set a breakpoint that exists even after restarting the process
> bl					# list the breakpoints
> bc 2					# delete breakpoint indexed at 2
> bc *					# delete all breakpoints

> a						# assemble x86 instructions
jmp esp

> !address				# displays address space of currently running process.
> !address 0x13000		# displays the properties of the address 0x13000
> !teb					# displays info. about 'Thread Exection Block'
> !exchain				# lists the currently registered exception handlers

> .load narly			# plugin module that identifies tables for SAFE SEH mitigations on dlls
> !nmod					# different mitigations on all loaded modules

> .load msec			# Loads probably microsoft security module
> !exploitable			# Checks if the crash is exploitable or not based on some heuristics

> .restart				# Restart the program
> .reload				# Reload the program
> .sympath				# Shows the symbol search path
> .symfix				# Use this command after changing the 'symbol path' to get changes done.

> ?					# To do arbitrary calculations on command line. masm evaluation
> ?esp+100			# gives the value of $esp+0x100
> ?esp+eax			# gives the value of $esp+$eax
> ?? <expression>	# C++ evaluation

# Command to read from memory
> da address	# x/s address : Reads an ASCII string from address			
> du address	# Reads a unicode string from adddress		
> dc address	# x/c address : Reads bytes and show the ASCII chars corresponding to bytes
> dd esp		# x/xw $esp
> dd ebp L2		# x/2w $ebp. Describe Dword starting at ebp. L2 is counts of Dword
> dd poi(esp)	# Poi command interpret args as pointers and tries to dereference the argument. It 
				# will look at top value on stack and interpret as a pointer

> k				# display stack backtrace info
> p				# ni -> step over
> t				# si -> step into

> x basic_vuln!prize		# Print the location of 'prize()' symbol in 'basic_vuln' module. (
> ln 0x10056				# Prints the nearest symbol pertaining to the address 0x10056
> poi(0x80104839)			# returns *0x80104839

> u address					# disassemble address
> u poi(ebp+0x4)			# disassemble $ebp+0x4
> ub address				# Unassemble backwards

> dg fs						# Display segment info. selected by fs register
> dt nt!_peb				# Display structure info on the peb structure defined in nt module


> lmvm binary_name			# Gives information about the binary
> lm						# list modules
> !lmi module_name			# info about a module
> s ntdll Lb2000 ff e4		# find "ff e4" instruction in ntdll, size is b2000
```