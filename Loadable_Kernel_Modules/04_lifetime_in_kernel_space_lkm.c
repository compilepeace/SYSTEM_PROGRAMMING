// Author: Abhinav Thakur
// Email : compilepeace@gmail.com
// Description : Module to determine the number of seconds the module lived in kernel space
// 		 (i.e. /var/log/kern.log) when loaded/removed from the kernel.


#include <linux/init.h>			// To get module_init() and module_exit() macros
#include <linux/module.h>		// Contains headers for loading modules into kernel
#include <linux/kernel.h>		// Contains types/macros/functions of the kernel
#include <linux/jiffies.h>		// jiffies keeps track of timer interrupts since system boot
#include <asm/param.h>			// defines the constant HZ


static unsigned long my_lifetime; 
static unsigned long my_jiffies;

// The keyword static will restrict the function to be visible to other .c files
static int getting_started(void)
{
	// Getting initial value of jiffies
	my_jiffies = jiffies;
	my_lifetime = 0;
	printk( KERN_INFO "Compilepeace: INSIDE THE KERNEL SPACE! \n");
	return 0;
}


// We'll use jiffies to get the number of timer interrupts since initialization (getting_started) up 
// till finalization (departure) function. Now, just divide this difference by timer frequency (HZ). 
static void departure(void)
{
	my_jiffies = jiffies - my_jiffies;
	my_lifetime = (my_jiffies / HZ);
	printk( KERN_INFO "Compilepeace stayed in the kernel for: %lu seconds !\n", my_lifetime);
}


module_init( getting_started );
module_exit( departure );

MODULE_AUTHOR("Abhinav Thakur (compilepeace)");                
MODULE_LICENSE( "GPL" );                                      
MODULE_DESCRIPTION( "A module to write the number of seconds the module lived in the kernel space to kernel log buffer - /var/log/kern.log");    
MODULE_VERSION( "0.1" );

