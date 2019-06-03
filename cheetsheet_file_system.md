

##	SYSCALLS

chmod			# Syscall to change permissions of a file
getuid			# returns the real user id
geteuid			# returns the effecive user id. If it returns 0,program is effectively running as root

ctime			# Translates data & time field of 'struct timespec' into ASCII string

fileno			# To get a file descriptor of a file stream
fdopen			# Associates a stream with an existing file descriptor

stat			# Returns metadata/information about the file
fstat			# same stat but works with file descriptor associated with file rather than filename.
lstat			# Same as stat except that if file is a symlink, returns info about link, not the file


opendir			# opens up the directory stream pointed to by name to performs other dir operations
readdir			# Returs a pointer to dirent structure representing the next directory entry.
closedir		# closes the directory handle
fdopendir		# like opendir, but returns a directory stream reffered to by the open fd.


##	COMMANDS

mknod			# To change the first bit of a file (i.e. filetype)
chmod			# To change the permissinos of file
chown			# change ownership of file



##	INODE
Forget about filenames, 'inode' is the file. Disk block contains directory entries (or dirent's) which is nothing more than a mapping of Inode number <---> filename.

```
critical@d3ad:~$ ls -i			# To list the inode numbers of a files in current directories
```
