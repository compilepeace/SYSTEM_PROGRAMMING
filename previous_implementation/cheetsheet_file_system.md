

##	SYSCALLS

chmod			# Syscall to change permissions of a file
getuid			# returns the real user id
geteuid			# returns the effecive user id. If it returns 0,program is effectively running as root

ctime			# Translates data & time field of 'struct timespec' into ASCII string

open			# open a file and returns a file descriptor
lseek			# Repositions file offset to the argument 'offset' acc. to directive 'whence' -
	> SEEK_SET	- File offset position is set to 'offset' bytes. 
	> SEEK_CUR	- File offset position is set to its current position + 'offset' bytes.
	> SEEK_END	- File offset position is set to the size of file + 'offset' bytes.

fileno          # To get a file descriptor of a file stream
fdopen          # Associates a stream with an existing file descriptor

stat			# Returns metadata/information about the file
fstat			# same stat but works with file descriptor associated with file rather than filename.
lstat			# Same as stat except that if file is a symlink, returns info about link, not the file


opendir			# opens up the directory stream pointed to by name to performs other dir operations
readdir			# Returs a pointer to dirent structure representing the next directory entry.
closedir		# closes the directory handle
fdopendir		# like opendir, but returns a directory stream reffered to by the open fd.

link			# Create hardlink between 2 files, i.e. A file having 2 names but 1 location.
symlink			# Create a symbolic link

mmap			# memory maps a file on disk to RAM (through file descriptors)
munmap			# unmaps the file from memory (releases the resources)
sync			# To synchronize the disk cache (writes) with HDD (persistent storage) immediately.
fsync			# All changes associated with a particular file descriptor are flushed to disk.


##	READ and WRITE BUFFER
Read first loads data from `disk` to `Page cache`, and the copy data from `Page cache` to user-space buffer.
Write puts data from user-space buffer to `Page cache` and then puts it to a fd (maybe a file standard file descriptors - STDIN(0), STDOUT(1), STDERR(2)).


##	MMAP and MUNMAP and DISK CACHE
Rules for mmap -

	> mmap requires a file descriptor, so we need to open the file first
	> mmap only works with lseek'able file descriptors, i.e. true files not sockets or pipes. 

Does anything written on mmaped area gets written to the disk too ??
Yes, any changes to the mmaped region gets reflected to the file in persistent storage HDD also. The memory mapped regions remains sync'd with file on disk via 'disk cache'. The file is first loaded into the disk cache before any read/write can occur and the writes are first performed on the disk cache rather than on hdd. The OS will synchronize the disk cache with HDD eventually. We can use sync() to do so immediately.


##	HOW TO SHARE MEMORY BETWEEN A PARENT AND CHILD PROCESS ??
Use `mmap` without a file, just specify the `MAP_ANONYMOUS` and `MAP_SHARED` flags.


##	COMMANDS

mknod				# To change the first bit of a file (i.e. filetype)
chmod				# To change the permissinos of file
chown				# change ownership of file

umask 077			# This will change the system settings, whenever a file will be created from now,
					# the 'rwx' bits will be masked out of new file for 'group' and 'others'.

Let's say I have a filesystem hooked up on /dev/cdrom that I want to read from. I have to mound it to a directory before I can do any operations.

sudo mount /dev/cdrom /media/cdrom	
mount
mount | grep proc

sudo mount -o loop file.iso /mount/directory


cat /proc/meminfo	# All information about memory 
cat /proc/cpuinfo	# Information about CPU architecture



##	STICKY BIT
When a file/directory's sticky bit is set then only the file/directory's owner and the root user is able to rename or delete the file.


##	TURN OFF EXECUTE BITS ON DIRECTORIES
Now, the directory itself is listable but its contents are not visible


##	INODE
Forget about filenames, 'inode' is the file. Disk block contains directory entries (or dirent's) which is nothing more than a mapping of Inode number <---> filename.

```
critical@d3ad:~$ ls -i			# To list the inode numbers of a files in current directories
```


##	VIRTUAL FILE SYSTEMS
These file systems do not exist on the disk but, they are generated dynamically by the kernel when a process requests a directory listing. Linux provides 3 main Virutal FS

```
/dev  - A list of physical and virtual devices (for example network card, cdrom, random number generator)
/proc - A list of resources used by each process and (by tradition) set of system information
/sys - An organized list of internal kernel entities

```


