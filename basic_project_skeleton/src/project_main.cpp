/********************************************************************************
 * Author   : Abhinav Thakur                                                    *
 * Email    : compilepeace@gmail.com                                            *
 * Filename : project_main.cpp                                                  *
 *                                                                              *
 * Description: Driver module for the project.                                  *
 *                                                                              *
 ********************************************************************************/


#include "peace_helper.h"


/* MACRO definitions */
#define DEBUG_INFO  __FILE__,__FUNCTION__,__LINE__

/* function prototypes */
void display_banner ();

/* ____ add external variable definitions */
int logfd = -1;


int main (int argc, char **argv) {

    parse_opts (argc, argv);

    /* ____ test/add code here */


    return 0;
}


void display_banner () {
	const char banner[] = "";

	system ("clear");
	fprintf (stderr, "\n\n\n\n%s\n", banner);
}
