#define _USE_BSD
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//including the source code
#include </afs/pitt.edu/home/f/o/foa5/Echo/passiveTCP.c>

#define QLEN 64
#define BUFSIZE  8192  
//set the buffer size

extern int errno;

//Defining the prototypes
void reaper(int);
int TCPechod(int fd);
int errexit(const char *format, ...);
int passiveTCP(const char *service, int qlen);

// main - Concurrent TCP server for ECHO service

int main(int argc, char *argv[])
{
	char *service = "echo";	
	struct sockaddr_in fsin;
	unsigned int alen;
	int msock; //master socket
	int ssock; //slave socket

	switch(argc) {
		case 1:
			break;
		case 2:
			service = argv[1];
			break;
		default:
			errexit("usage: TCPechod [port]\n");
	}

	msock = passiveTCP(service, QLEN);

	(void) signal(SIGCHLD, reaper);

	while (1) { // waiting for a request to come through
		printf("\nWaiting a request from the client \n");
		alen = sizeof(fsin);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen); //accept the request
		if (ssock < 0) {
			if (errno == EINTR)
				continue;
			errexit("accept: %s\n", strerror(errno));
		}
		switch (fork()) {
		case 0:	//child process
			(void) close(msock);
			exit(TCPechod(ssock));
		default: //parent process
			(void) close(ssock);
			break;
		case -1:
			errexit("fork: %s\n", strerror(errno));
		}
	}
}

//TCPechod - echo data unitl end of file

int TCPechod(int fd)
{
	char buf[BUFSIZ];
	int	cc;

	while (cc = read(fd, buf, sizeof buf)) {
		printf("\nJust got the message sent by the client --> %s \n", buf); 
		if (cc < 0)
			errexit("echo read: %s\n", strerror(errno));
		if (write(fd, buf, cc) < 0)	// sent back the request to the client
			errexit("echo write: %s\n", strerror(errno));
		printf("\nSent the message back to the client --> %s \n", buf);		
		
	}
	return 0;
}

//reaper - clean up zombie children

void reaper(int sig){
	int status;
	while (wait3(&status, WNOHANG, (struct rusage *)0) >= 0)
		/*empty*/;
}
			
		
