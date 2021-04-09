// Author: Abhinav Thakur
// Email : compilepeace@gmail.com
// Description : Module to display system uptime value (in seconds) to kernel log buffer 
// 		 (i.e. /var/log/kern.log) when loaded/removed from the kernel.


#include <linux/init.h>			// To get module_init() and module_exit() macros
#include <linux/module.h>		// Contains headers for loading modules into kernel
#include <linux/kernel.h>		// Contains types/macros/functions of the kernel
#include <linux/jiffies.h>		// declares the value of jiffies (global variable)
#include <asm/param.h>			// defines the tick rate (value of HZ or frequency of timer interrupts) 


// The keyword static will restrict the function to be visible to other .c files
static int getting_started(void)
{
	// jiffies store the number of timer interrupts that have occured since the system boot
	// HZ stores the interrupt frequency (i.e. number of timer interrupts in 1 second)
	printk( KERN_INFO "System uptime is: %lu seconds (since the system booted)\n", jiffies/HZ); 
	return 0;
}


static void departure(void)
{
	printk( KERN_INFO "Tata! \n");
}


// Registering the initialization and finalization routines
module_init( getting_started );
module_exit( departure );


// 1. Visible when using modinfo
// 2. Affects the runtime behaviour
// 3. Visible when using modinfo
MODULE_AUTHOR("Abhinav Thakur (compilepeace)");                // <1>
MODULE_LICENSE( "GPL" );                                       // <2>
MODULE_DESCRIPTION( "A module to display system uptime value to kernel log buffer - /var/log/kern.log");    //<3>
MODULE_VERSION( "0.1" );

