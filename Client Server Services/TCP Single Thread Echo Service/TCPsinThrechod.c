#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

//including the source code
#include </afs/pitt.edu/home/f/o/foa5/Echo/passiveTCP.c>

#define QLEN 32
#define BUFSIZE  4096

extern int errno;

//defining the prototypes
int errexit(const char *format, ...);
int passiveTCP(const char *service, int qlen);
int echo(int fd);
int count=0;   // added to count the clients

//main - Concurrent TCP server for ECHO service

int main(int argc, char *argv[])
{
	char *service = "echo";	
	struct sockaddr_in fsin;	
	int msock;
	fd_set	rfds;
	fd_set	afds;	
	unsigned int alen;
	int	fd, nfds;

	switch(argc) {
		case 1:
			break;
		case 2:
			service = argv[1];
			break;
		default:
			errexit("usage: TCPmechod [port]\n");
	}

	msock = passiveTCP(service, QLEN);// make the connection

	nfds = getdtablesize();
	FD_ZERO(&afds);
	FD_SET(msock, &afds);


	while(1) {
		printf("\nWaiting a request from the client \n");
		memcpy(&rfds, &afds, sizeof(rfds));

		if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0,(struct timeval *)0) < 0)
			errexit("select: %s\n", strerror(errno));

		if (FD_ISSET(msock, &rfds)) {
			int	ssock;
			alen = sizeof(fsin);
			ssock = accept(msock, (struct sockaddr *)&fsin,&alen);
			if (ssock < 0)
				errexit("accept: %s\n",
					strerror(errno));
			FD_SET(ssock, &afds);
		}
		for(fd =0; fd<nfds; ++fd)
			if(fd != msock && FD_ISSET(fd, &rfds))
				if(echo(fd) == 0) {
					(void) close(fd);
					FD_CLR(fd, &afds);
				}
	}
}


//echo - echo one buffer of data, retruning byte count

int echo(int fd){	
	char buf[BUFSIZE];
	int cc;
	cc = read(fd, buf, sizeof buf);
	count = count +1;    // to count the clients .. added
	printf("\nJust got the message sent by the client %d --> %s \n",count, buf);
	if(cc < 0)
		errexit("echo read: %s\n", strerror(errno));
	printf("\nJust sent the message got from the client %d --> %s \n",count, buf);
	if(cc && write(fd, buf, cc) < 0)
		errexit("echo write: %s\n", strerror(errno));
	return cc;
}