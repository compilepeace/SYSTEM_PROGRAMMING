
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#include "color.h"

#define MS1 "0xdarkmagician was here "
#define MS2 "And so was Mahakaal"

int main()
{
	int pipe1[2];					// Parent writes to pipe1 and child reads MS1 from this pipe1
	int pipe2[2];					// Child then appends MS1 and MS2 then writes to pipe2. Parent then reads from pipe2

	// Create 1st pipe and Handle error
	if ( pipe(pipe1) == -1 )
	{
		perror(RED"[-]"RESET" While creating pipe1: ");
		exit(0x10);
	}

	// Create 2nd pipe and Handle error
	if ( pipe(pipe2) == -1 )
	{
		perror(RED"[-] "RESET"While creating pipe2: ");
		exit(0x11);
	}


	pid_t id = fork();			// fork a child process


	if ( id < 0 )
	{
		perror("fork(): ");
		exit(0x12);
	}

	// Parent block
	if ( id > 0 )
	{
		// close read end of pipe1 and write to the write end of pipe1
		close( pipe1[0] );
		write(pipe1[1], MS1, strlen(MS1));
		close( pipe1[1] );
		fprintf(stdout, GREEN"[+]"RESET" (In parent) Wrote to pipe1: "YELLOW MS1"\n");

		wait(NULL);				// Wait for the child process to send back string from 2nd pipe

		
		// Now, close the write end of 1st and 2nd pipe and read from the read end of pipe2
		close( pipe2[1] );

		char Pbuffer[strlen(MS1) + strlen(MS2) + 1];		// Parent buffer stores concatenation of string MS1 & MS2
		read(pipe2[0], Pbuffer, sizeof(Pbuffer));
	
		fprintf(stdout, GREEN"[+]"RESET" (In parent) Recieved from pipe2: "YELLOW"%s\n", Pbuffer);	
	}

	// Child block
	if ( id == 0 )
	{
		char Cbuffer[ strlen(MS2) + strlen(MS1) + 1 ];				// Child buffer
		char *temp = MS2;

		// close write end of 1st pipe and read from the read end of pipe1
		close( pipe1[1] );
		read(pipe1[0], Cbuffer, strlen(MS1));
		fprintf(stdout, GREEN"[+]"RESET" (In child) Read from pipe1: "YELLOW"%s\n", Cbuffer);

		// Concatenate MS2 to Cbuffer containing MS1
		int i;
		for (i=0 ; i < strlen(MS2); ++i)
		{
			Cbuffer[strlen(MS1) + i] = *(temp + i) ;
		}
		Cbuffer[strlen(MS1) + strlen(MS2)] = '\x00';	// Terminating the concatenated string
	
	
		// Closing reading end of pipe2 and Writing Fbuffer into pipe2
		close( pipe2[0] );
		write( pipe2[1], Cbuffer, sizeof(Cbuffer) );
		
		fprintf(stdout, GREEN"[+] "RESET"(In child) Wrote to pipe2: "YELLOW"%s\n", Cbuffer);
	}

return 0;
}
