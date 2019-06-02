// Author : Abhinav Thakur
// Email  : compilepeace@gmail.com

// Description : This is a simple client program leveraging socket->connect->read/write syscalls

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
#include <signal.h>

#include "color.h"

#define PORT "80"

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


int main(int argc, char *argv[])
{
	int sockfd, connect_status;


	// Register a signal handler function for SIGPIPE
    signal(SIGPIPE, sigpipe_handler);


	// Check for command line arguments
	if (argc < 2)
	{
		fprintf(stderr, RED"[-]"RESET" Usage: %s <host_name>\n", argv[0]);
		exit(0x10); 
	}

	// Create a non-blocking socket 
	sockfd = socket( AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0 );
	if (sockfd == -1)
	{
		perror(RED"[-] In socket(): ");
		exit(0x11);	
	}

	
	// configure sockaddr structure for server you want to connect. Use getaddrinfo to do so and store
	// the server info into the resulting structure.
	struct addrinfo hints, *results;
	memset(&hints, '\0', sizeof(struct addrinfo));
	hints.ai_family = AF_INET;						// For IPv4	
	hints.ai_socktype = SOCK_STREAM;				// For Transmission Control Protocol
	
	int status = getaddrinfo(argv[1], PORT, &hints, &results);
	if (status != 0)
	{
		fprintf(stderr, RED"[-]"RESET" getaddrinfo: %s", gai_strerror(status));
		exit(0x12);
	}


	// Connect through the resulting structure returned by getaddrinfo (server)
	connect_status = connect( sockfd, results->ai_addr, results->ai_addrlen);
	if (connect_status == -1)
	{
		perror(RED"[-] In connect(): ");
		exit(0x13);
	}

	// After connection is established, send a HTTP request
	char *request = "GET / HTTP/1.1\r\n\r\n";	
	fprintf(stdout, GREEN"[+]"RESET" Sent: %ld bytes ===> "YELLOW"%s"RESET, strlen(request), request );
	write(sockfd, request, strlen(request));


	// Read response for HTTP request sent
	char response[3000] = {};	
	int bytes_read = read(sockfd, response, 3000-1);
	response[bytes_read] = '\0';
	fprintf(stdout, GREEN"[+]"RESET" Recieved: %d bytes\n\n", bytes_read);

	// Print the response from webserver
	fprintf(stdout, GREEN"[+]"RESET" Resonse : %s\n\n", response);


return 0;
}	

