// Author: Abhinav Thakur
// Email : compilepeace@gmail.com
// Description : Module that simply displays the greatest common divisor value to kernel log buffer 
// 		 (i.e. /var/log/kern.log) when loaded/removed from the kernel.


#include <linux/init.h>			// To get module_init() and module_exit() macros
#include <linux/module.h>		// Contains headers for loading modules into kernel
#include <linux/kernel.h>		// Contains types/macros/functions of the kernel
#include <linux/gcd.h>			// defines unsigned long gcd(unsigned long, unsigned long);


// The keyword static will restrict the function to be visible to other .c files
static int getting_started(void)
{
	printk( KERN_INFO "Greetings! remove the module to see gcd(3330 and 24) \n");
	return 0;
}


static void departure(void)
{
	unsigned long result = gcd(3330, 24);
	printk( KERN_INFO "Greatest Common Divisor gcd(3330, 24): %lu\n", result);
}


// Registering the initialization and finalization routines
module_init( getting_started );
module_exit( departure );


// 1. Visible when using modinfo
// 2. Affects the runtime behaviour
// 3. Visible when using modinfo
MODULE_AUTHOR("Abhinav Thakur (compilepeace)");                // <1>
MODULE_LICENSE( "GPL" );                                       // <2>
MODULE_DESCRIPTION( "A module to display greatest common divisor of 3330 and 24 -> value to kernel log buffer - /var/log/kern.log");    //<3>
MODULE_VERSION( "0.1" );

