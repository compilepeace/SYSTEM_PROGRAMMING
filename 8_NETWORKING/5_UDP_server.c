// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : This is a UDP server implementation



#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "color.h"

#define PORT "10000"


int main(int argc, char *argv[])
{
	struct addrinfo hints, *results;


	// configure the structure for UDP server configuration
	memset(&hints, '\0', sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_flags = AI_PASSIVE;


	// returns a linked-list of results in 'results' structure
	getaddrinfo(NULL, PORT, &hints, &results);

	
	// Create a socket
	int sockfd = socket(results->ai_family, results->ai_socktype | SOCK_NONBLOCK, results->ai_protocol);
	if (sockfd == -1)
	{
		perror(RED"[-]"RESET" In socket: ");	
		exit(0x10);
	}


	// Bind that socket to configured structure 'results' returned by getaddrinfo()
	if ( ( bind(sockfd, results->ai_addr, results->ai_addrlen) ) != 0)
	{
		perror(RED"[-]"RESET" In bind: ");
		exit(0x11);
	}


	struct sockaddr_storage client_addr;
	int clientaddr_size = sizeof(struct sockaddr_storage);


	while (1)
	{
		char message[1000];

		int bytes_recieved = recvfrom( sockfd, message, sizeof(message), 0,
									  (struct sockaddr *) &client_addr, &clientaddr_size);
		message[bytes_recieved] = '\0';

		fprintf(stdout, GREEN"[+]"RESET" Read %d bytes: %s\n", bytes_recieved, message);
	}
return 0;
}
