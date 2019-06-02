// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : This program uses getifaddrs() to get interface addresses on a machine.



#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <ifaddrs.h>
#include <unistd.h>

#include "color.h"



int main()
{
	struct ifaddrs *myaddr, *ptr;

	char host_ip[100], host_service[100];

	// See manual of getifaddrs : for network interfaces
	getifaddrs(&myaddr);

	for (ptr = myaddr; ptr != NULL; ptr = ptr->ifa_next )
	{
		getnameinfo( ptr->ifa_addr, sizeof(struct sockaddr_in),
					 host_ip, sizeof(host_ip),
					 host_service, sizeof(host_service),
					 NI_NUMERICHOST | NI_NUMERICSERV );

		fprintf(stdout, GREEN"[+]"RESET" Found interface"YELLOW" %s"RESET":"RED" %s\n", 
				host_ip, host_service);	
	
	}

return 0;
}
