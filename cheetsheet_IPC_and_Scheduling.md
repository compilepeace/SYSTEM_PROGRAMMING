```
@ All Notes are from Angrev's sytem programming tutorial plus my own addon's. Some concepts can be incorrect also (due to my addon's).
Also Read : "https://cseweb.ucsd.edu/classes/sp16/cse120-a/applications/ln/lecture11and12.html"
Paging : "http://wiki.osdev.org/Paging"
```
**NOTE** : If we use -std=gnu99 with GCC while compiling, we can get rid of the C standard's restriction and lets us use the POSIX and GNU-only extension.

##	SYSCALLS

**NOTE** : Everything is copied over to the child process including the file handles as well as the relative positions of the files.

```
mmap			# Generally used to map a file into memory, reserving some space in the process address space for the file.
munmap			# Once done with operations on file in memory, you tell OS that you're no longer using
				# the pages allocated by mmap, so the OS can write it back to the disk and give you 
				# the addresses back in case you need to malloc later

eg:	
	...
	int fd = open(...)				// File has 2 pages
	char *addr = mmap (..fd..)		// map the file into memory (process address space)
	addr[0] = '1';					// Place the character '1' at first byte in file opened in memory 
	...


pipe			# Used to create a pipe
fdopen			# Takes in fd, unlike fopen (which takes in filename as parameter). Use it to deal with pipes
mkfifo			# create named pipes (FIFO's)


FILE OPERATIONS VIA FILE DESCRIPTORS
open			# open a file descriptor (file, pipes etc._
read			# read from file descriptor 
write			# write to file descriptor
close			# close file descriptor
lseek			# reposition read/write file offset
fcntl			# manipulate file descriptor


FILE OPERATIONS VIA FILE POINTERS
fopen			# open file stream
fread/fscanf	# read from opened file
fgetc/fgets		# read a character/string from file
fwrite/fprintf	# write to opened file via FILE pointer
fclose			# close file stream
fflush			# flush the stream
fseek			# seek to an offset in file. Write/Read to file will change the current position.
ftell			# To obtain current value of the file position indicator for stream
```



##	PAGES (Corresponds to blocks of virtual memory)
On a typical 32-bit machine, a page size is 4KB.

	
	Total size of addressable memory on a 32-bit machine = 2^32 Bytes
	Size of 1 page = 4KB = 2^2 * 2*10 bytes = 2^12 bytes

Therefore,	

	Total no. of pages in a 32-bit machine	=   Total size of addressable memory (in bytes)
	                                            --------------------------------------------
	                                                    Size of 1 page (in bytes)

	Total no. of pages in a 32-bit machine	=	2^32 / 2^12	= 	2^20

	
	Size of a Frame = Size of a Page

	Total no. of frames in a 32-bit machine	= 2^20



##  FRAMES (Corresponds to blocks of physical memory - RAM)
Frames are created by dividing actual physical memory (RAM) into fixed sized blocks. They are same in number and size as that of Page Tables.



##	PAGE TABLE (requires 4 MB of physical memory on 32-bit systems)
A simple page table is just an array, where each PTE (Page table entry) stores a frame number,  i.e.

	int frame = table[ page_number ];		// table consists of the PTE's as its elements

A simple 32-bit machine, each PTE needs to hold a frame number (i.e. 20 bits as we calculated 2^20 frames), i.e. 2.5 bytes per entry ! We round off it to 4 Bytes per entry and put rest of the bits for some other use.

With 4 Bytes per entry and 2^20 entries, 4 MB of physical memory is required to hold a page table.
	i.e.
			4 Bytes x 2^20 entries	=	4 MB of physical memory (to hold page table)



##	OFFSETS
This is how we calculate which particular byte to use inside a particular frame. Above, we mentioned in PAGE TABLE heading, each PTE needs only 20 bits, we give them 24 bits, and we use the lowest 8 bits of virtual memory address directly. Suppose our process is reading the following virtual address - 

	VirtualAddress = 11110000111100001111000010101010 (binary)

On a machine with page size 256 Bytes, the lowest 8 bits (10101010) will be used as the offset. The remaining upper bits will be the page number (111100001111000011110000).



##	MULTI-LEVEL PAGE TALBLES
These are solutions to the page table size issue in 64 bit architectures. Each table is a list of pointers that point to the next level of tables.

```
	VirtualAddress = 11110000111111110000000010101010 (binary)
                     |_Index1_||        ||          | 10 bit Directory index
                               |_Index2_||          | 10 bit Sub-table index
                                         |__________| 12 bit offset (passed directly to RAM)
```

20 bits for (Index1 + Index2), i.e. we can now divide the virtual address into 3 fields - 
	
	>   Index 1      : The directory (or Page Table Directory)
	>   Index 2      : Page Number
	>   Rest 12 bits : Offset



##	TLB (Translation Lookaside buffer) (associated cache of recently used "virtual-page-to-frame" lookups)
For a single page table, machine is twice as slow since 2 memory accesses are done (i.e. one to access PTE and other to access page frame of RAM), For a two-level page table, machine is thrice as slow since 3 memory accesses are performed (i.e. one for the page table directory, one for the page number and one for the offset in page frame).

To overcome this access-time overhead, the MMU includes an associative cache of recently used "virtual-page-to-frame" lookups. This cache is called TLB ("Translation Lookaside Buffer").

Everytime a logical/virtual address needs to be translated into a physical memory location, the TLB is 	queried in parallel to the Page Table.



##	WHAT ALL DOES THE PAGE TABLE STORES ?
In addition to storing the frame number, the page table can be used to stores the attributes of the corresponding frame ( at least Read/Write permissions, modification and execution information ). 

**NOTE** :	The C-Library instructions code (.code segment) can be shared between all processes that  dynamically load code into the process memory. Each process can read that memory but a write would result in a SIGSEGV (Segmentation Fault).



##	MMAP syscall
Processes can share a page with child process via "mmap" system call. MMAP instead of tying each virtual address to a physical frame, it can tie virtual address to a file, a GPU unit or can perform any other memory mapped operation you can think of! Further writing to that memory address may result into writing to that file/device etc.



##	PAGE FAULTS
When a running process tries to access some virtual memory address in its address space that is not mapped to a physical memory location.

There are 3 types of page faults -

```
> Minor	: If there is no mapping yet (for the page), but is a valid address. The OS simply makes the page, loads it into memory and moves on.

> Major	: If the mapping to the page is not in memory but on disk. What this will do is swap the page into memory and swap another page out. If this happens frequently, your program is said to "THRASH" the MMU.

> Invalid : When you try to write to a non-writable or read to a non-readable memory address. This type of page fault happens during program crash (when the MMU generates an invalid fault and OS generates a SIGSEGV).
```

###	Read-Only bit
NOTE :	Two examples where Read-Only bit is marked on a Page are -

```		
> Sharing C runtime library between multiple processes (no modifications to libraries allowed)

> CoW (Copy-on-Write) where the cost of duplicating a page can be delayed until the first write occurs. This generally happens when we fork a process, the page isn't duplicated in memory until any write on the page happens. CoW is also known as "implicit sharing" or "shadowing".
```

###	Dirty bit (Modified bit)
This bit is set when a paged-in memory is modified. This bit marks that if a page is modified in memory, then it must be backed out to the backing store (i.e. page is swapped out and the modifications are written to the disk). It  A page on disk that is paged in to physical memory, then read from, and subsequently paged out again does not need to be written back to disk, since the page hasn't changed. It saves the memory write operations. Read more "https://en.wikipedia.org/wiki/Page_table#Page_table_data" 

###	Execution bit (Relate to NX bit set for DEP)
If this bit is set, it marks the page as Executable. NX(Non-Executable) bit is set in the attributes of pages (in PTE's) so as to mark all pages in stack Non-Executable and prevents any malacious code injected into the stack region of process memory from being executed (i.e. stack overflow).

**Read mode** :  "https://en.wikipedia.org/wiki/NX_bit#Hardware_background".
	
s
