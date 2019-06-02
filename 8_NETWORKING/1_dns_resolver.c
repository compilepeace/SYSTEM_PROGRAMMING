// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : This program illustrates the use of getaddrinfo and getnameinfo to take information
//               of a server and get its IP address via hostname, i.e. a working of a DNS.


/*

struct addrinfo {
	int              ai_flags;
	int              ai_family;
	int              ai_socktype;
	int              ai_protocol;
	socklen_t        ai_addrlen;
	struct sockaddr *ai_addr;
	char            *ai_canonname;
	struct addrinfo *ai_next;
};

*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

#include "color.h"


// int getaddrinfo(const char *node, const char *service,
//                       const struct addrinfo *hints,
//                       struct addrinfo **res);

// int getnameinfo(const struct sockaddr *addr, socklen_t addrlen,
//                       char *host, socklen_t hostlen,
//                       char *serv, socklen_t servlen, int flags);



// global variables so that we don't need to memset to 0's
struct addrinfo hints, *results;


int main(int argc, char *argv[])
{
	char host_name[16];
	

	if (argc < 2)
	{
		fprintf(stderr, RED"[-]"RESET" Usage: %s <domain_name>\n", argv[0]);
		exit(0x10);
	}

	
	// filling in fields of hint (struct addrinfo) before giving it to getaddrinfo to get information
	// of the host specified into hints structure.
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	

	// get linked-list of addrinfo structures containing IP addresses, i.e. domain name => IP addr
	int status = 0;
	status = getaddrinfo(argv[1], NULL, &hints, &results);	
	if (status != 0)
	{
		// if getaddrinfo fails
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		exit(0x11);
	}


	struct addrinfo *i;	

	// parse the linked-list (*result ) which is a list of result structures returned by getaddrinfo 
	for ( i = results ; i != NULL ; i = i->ai_next )
	{
		getnameinfo( i->ai_addr, i->ai_addrlen, host_name, sizeof(host_name), NULL, 0, NI_NUMERICHOST);	
		fprintf(stdout, GREEN"\n[-]"RESET" %s : "YELLOW"%s\n\n", argv[1], host_name);	
	}
	
	
	// Freeing the results structure
	freeaddrinfo(results);

return 0;
}
