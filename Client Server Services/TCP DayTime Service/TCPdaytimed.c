
#include <sys/types.h>
#include <sys/socket.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <time.h>

#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/passiveTCP.c>
//#include <errexit.c>



extern int errno;
void TCPdaytimed(int fd);
int errexit(const char *format, ...);
int passiveTCP(const char *service, int qlen);

#define QLEN 32
#define time_t long


/*
	main - TCP clinet for DAYTIME service
*/

int main(int argc, char *argv[])
{
	struct sockaddr_in fsin;
	char *service = "daytime";
	int msock, ssock;
	unsigned int alen;

	switch(argc) {
		case 1:
				break;
		case 2:
				service = argv[1];
				break;
		default:
			errexit("usage: TCPdaytimed [port]\n");
	}

	msock = passiveTCP(service, QLEN);

	while(1) {
		alen = sizeof(fsin);
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen);
		if(ssock < 0)
			errexit("accept failed:%s\n", strerror(errno));
		TCPdaytimed(ssock);
		(void) close(ssock);
	}
	

}

/* TCPdaytimed - */

void TCPdaytimed(int fd)
{
	char *pts;
	time_t now;
	char *ctime();

	(void) time(&now);
	pts = ctime(&now);
	(void) write(fd, pts, strlen(pts));
}







