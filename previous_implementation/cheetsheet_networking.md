```
@ All Notes are from Angrev's sytem programming tutorial plus my own addon's. Some concepts can be incorrect also (due to my addon's).

Refference
TCP handshake => https://www.inetdaemon.com/tutorials/internet/tcp/3-way_handshake.shtml
```

##	SYSCALLS
getnameinfo is the most usefull which eliminates the need to extract IP address from structures, consider the bellow given snippet where accept stores the client information in client_info (of type struct sockaddr_storage) and then getnameinfo uses that structure to translate the client information from client_info structure to numeric IP/port.
getnameinfo takes out the IP address and port number from client information (struct sockaddr_storage) and puts it into client_ip[100] and port[100] for to print/use these IP/Port as strings.

``` 

        int client_fd = accept(sockfd, (struct sockaddr *)&client_info, &clientaddr_size );
        getnameinfo((struct sockaddr *) &client_info, clientaddr_size, client_ip, sizeof(client_ip), port, sizeof(port), NI_NUMERICHOST | NI_NUMERICSERV );
```
```
	// To create a non-blocking socket
	fd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
```

getaddrinfo					# returns linked-list of addrinfo structures, each of which contains IP's
getnameinfo					# inverse of getaddinfo, converts socket address => host/service name.
socket						# Create a socket
connect						# Connect to a socket fd via configured addrinfo structure(by getaddrinfo)
read						# read bytes from file descriptor
write						# write bytes to a file descriptor
setsockopt					# Generally used to reuse a port
bind						# bind socket fd to an address
listen						# listen for backlog no. of connections on a socket fd
accept						# wait for clients to connect. Returns a handle on successful connection.
getifaddrs					# What's my IP address. Get interface addresses. Parse the linkedlist and
							# use getnameinfo to print host IP address

select						# Synchronous I/O multiplexing
epoll						# I/O even notification facility

strerror(errno)				# To get short englist description of error
strerror_r					# Less portable, thread safe version of strerror
perror						# Thread safe to describe error
gai_strerr					# To convert returned error no. to a string



##	errorno
This is a special integer which is set when a system call fails. Initial value is 0 and a value of -1 is set when a syscall fails. Each thread has its own copy of errno.


##	EINTR
Some system calls can be interrupted when a signal (e.g SIGCHLD, SIGPIPE,...) is delivered to the process. At this point the system call may return without performing any action. This interruption can be detected by checking the return value and if errno is EINTR.


##	3 WAY TCP HANDSHAKE (SYN, SYN-ACK, ACK)
