// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : This is a simple webserver program leveraging socket->bind->listen->accept syscalls

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
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>
#include <ifaddrs.h>

#include "color.h"


#define PORT "10000"
#define GREETING "0xdarkmagician is here\n"

// int getaddrinfo(const char *node, const char *service,
//                       const struct addrinfo *hints,
//                       struct addrinfo **res);



// A signal handler
void sigpipe_handler(int signal)
{
	char msg[1000];
	sprintf(msg, RED"[-]"YELLOW" ***** SIGPIPE - no one is listening *****\n");
	
	write(1, msg, strlen(msg) );
}


int main()
{

	// Register a signal handler function for SIGPIPE
	signal(SIGPIPE, sigpipe_handler);

    // Create a socket (a non-blocking socket)
	int sockfd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
	if (sockfd == -1)
	{
		perror(RED"[-]"RESET" In socket: ");
		exit(0x10);
	}


	// Configure the webserver by using getaddrinfo (rather than doing manually)
	struct addrinfo hints, *results;
	
	memset(&hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE;				// For wildcard IP address

	int status = getaddrinfo(NULL, PORT, &hints, &results);
	if (status != 0)
	{
		fprintf(stderr, RED"[-]"RESET" getaddrinfo: %s\n", gai_strerror(status));
		exit(0x11);
	}


	// Reuse any existing port
	int optvalue = 1;
	if ( ( setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, &optvalue, sizeof(optvalue)) ) != 0 )
	{
        perror(RED"[-]"RESET" listen(): ");
		exit(0x11);    
	}
	


	// Bind the socket with server configuration structure (configured using getaddrinfo above)
	if ( (bind(sockfd, results->ai_addr, results->ai_addrlen)) != 0 )
	{
		perror(RED"[-]"RESET" bind(): ");
		exit(0x12);
	}	

	// listen for at most 10 connections on the socket
	if ( (listen(sockfd, 10)) != 0 )
	{
        perror(RED"[-]"RESET" listen(): ");
        exit(0x12);
	}





	// PRINTS OUT ALL THE NETWORK INTERFACES OF A SYSTEM
	// Print out our machine's IP address and open port number before waiting for connections
	struct ifaddrs *myaddr, *ifa;
	char host_ip[100], host_port[100];
	getifaddrs(&myaddr);				// Returns a linked-list of resulting structures 
	
	// Now parse the linked-list pointed to by myaddr
	for (ifa = myaddr; ifa != NULL; ifa = ifa->ifa_next)
	{
		getnameinfo( ifa->ifa_addr, sizeof(struct sockaddr_in),
					 host_ip, sizeof(host_ip), host_port,
					 sizeof(host_port),
					 NI_NUMERICHOST| NI_NUMERICSERV
				   );
		
		fprintf(stdout, GREEN"[+]"RESET" Machine is running on %s: %s\n", host_ip, host_port);
	}





	// accept
	while (1)
	{
		struct sockaddr_storage client_info;
		socklen_t clientaddr_size = sizeof(client_info);		

		fprintf(stdout, GREEN"[+]"YELLOW" Waiting for connections...\n\n"RESET);
		int client_fd = accept(sockfd, (struct sockaddr *)&client_info, &clientaddr_size );

	
		char client_ip[300], port[300];
	
		// translate client info recieved by accept into client_info (of type struct sockaddr_storage)
		getnameinfo((struct sockaddr *) &client_info, clientaddr_size, client_ip, sizeof(client_ip), port, sizeof(port), NI_NUMERICHOST | NI_NUMERICSERV );
	
		fprintf(stdout, GREEN"[+]"RESET" Connection established (fd:%d) with %s: %s\n", client_fd, client_ip, port );	

		
		if (client_fd < 0)
		{
			perror(RED"[-]"RESET" accept(): ");
       		exit(0x12);
		}

		// send a greeting and close client connection
		write(client_fd, GREETING, strlen(GREETING));
		shutdown(client_fd, SHUT_WR);
		close(client_fd);
	}


	shutdown(sockfd, SHUT_WR);
	close(sockfd);

return 0;
}
