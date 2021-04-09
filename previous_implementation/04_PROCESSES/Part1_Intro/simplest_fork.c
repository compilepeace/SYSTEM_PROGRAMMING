

#include <stdio.h>
#include <unistd.h>

int main()
{
	printf("This will be printed only once\n");

	// CoW : Copy-on-write (or implicit sharing or shadowing), a resource management technique is
	// used within fork() syscall instead of the earlier version of fork() which used to copy the
	// parent process's virtual address space was used.
	fork();

	// Now 2 processes are running and therefore bellow lines will be executed twice.
	printf("This will be printed twice\n");

return 0;
}
