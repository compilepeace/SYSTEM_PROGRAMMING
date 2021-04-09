/*
 * Author: Abhinav Thakur
 * Email : compilepeace@gmail.com
 * 
*/


#include <linux/init.h>				// Contains module_init() and module_exit()
#include <linux/module.h>			// Contains headers for loading modules into the kernel
#include <linux/kernel.h>			// Contains types/macros/functions of the kernel
#include <linux/jiffies.h>			// Defines the global variable jiffies
#include <linux/proc_fs.h>			// Gives - proc_create() and remove_proc_entry()
#include <linux/uaccess.h>			// Gives - copy_to_user()

#define PROC_NAME "seconds"
#define BUF_SIZE 0x100


ssize_t my_proc_read( struct file *file, char __user *user_buffer, size_t count, loff_t *pos);

// Declaring what operations can be performed in the /proc/jiffies entry
static struct file_operations proc_ops = { .owner = THIS_MODULE, .read  = my_proc_read };

static unsigned long my_jiffies;


static int sarg(void)
{
	my_jiffies = jiffies;
	printk( KERN_INFO "Adding an entry to proc FS - /proc/seconds\n");

	// Create a /proc entry name seconds
	proc_create( PROC_NAME, 0755, NULL, &proc_ops );
	return 0;
}


static void nasht(void)
{
	// Remove the /proc/seconds entry created in sarg()
	remove_proc_entry( PROC_NAME, NULL );
	printk( KERN_INFO "Removed /proc/" PROC_NAME " entry \n");
}


// This function gets repeatedly called each time /proc/jiffies file is read until it returns 0
ssize_t my_proc_read( struct file *file, char __user *user_buffer, size_t count, loff_t *pos)
{
	unsigned long seconds_elapsed = (jiffies - my_jiffies) / HZ;
	static int completed = 0;
	int bytes_written = 0;
	char kernel_buffer[BUF_SIZE];	

	if (completed) {
		completed = 0;
		return 0;
	}

	completed = 1;

	bytes_written = sprintf(kernel_buffer, "Seconds elapsed since the module is residing in kernel space now: %lu\n", seconds_elapsed );

	// Copy kernel space memory (kernel_buffer) to user space memory (user_buffer)
	copy_to_user( user_buffer, kernel_buffer, bytes_written);

	return bytes_written;
}


module_init( sarg );
module_exit( nasht );

MODULE_LICENSE( "GPL" );
MODULE_AUTHOR( "Abhinav Thakur (aka Compilepeace)" );
MODULE_DESCRIPTION( "Returns user with a buffer (storing the seconds elapsed since the module is loaded into the kernel) whenever /proc/seconds file is read" );
