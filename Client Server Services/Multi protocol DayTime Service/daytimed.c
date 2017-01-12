#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>


#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/passiveTCP.c>
#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/passiveUDP.c>

#define	QLEN 5
#define	LINELEN	128
extern int errno;

//define daytime, errexit, passiveUDP and passiveTCP prototypes
int daytime(char buf[]);
int errexit(const char *format, ...);
int passiveTCP(const char *service, int qlen);
int passiveUDP(const char *service);

#define	MAX(x, y)	((x) > (y) ? (x) : (y))




int main(int argc, char *argv[]) {

	char	*service = "daytime";		
	char	buf[LINELEN+1];		
	struct sockaddr_in fsin;	 
	unsigned int	alen;			
	int	tsock; 			
	int	usock;			
	int	nfds;
	fd_set	rfds;		

	switch (argc) {
	case	1:
		break;
	case	2:
		service = argv[1];
		break;
	default:
		errexit("usage: daytimed [port]\n");
	}

	tsock = passiveTCP(service, QLEN);
	usock = passiveUDP(service);
	nfds = MAX(tsock, usock) + 1;	

	FD_ZERO(&rfds); // zero up file descriptor

	while (1) {
		printf("\nWaiting a request from the client \n");
		FD_SET(tsock, &rfds); //set tcp sock to file descriptor
		FD_SET(usock, &rfds); //set udp sock to file descriptor

		if (select(nfds, &rfds, (fd_set *)0, (fd_set *)0, (struct timeval *)0) < 0)
			errexit("select error: %s\n", strerror(errno));
		if (FD_ISSET(tsock, &rfds)){
			printf("\a request via TCP \n");
			int ssock;	

			alen = sizeof(fsin);
			// accept the request and create a slave soock
			ssock = accept(tsock, (struct sockaddr *)&fsin, &alen); 
			if (ssock < 0)
				errexit("accept failed: %s\n", strerror(errno));
			
			daytime(buf);
			(void) write(ssock, buf, strlen(buf));
			// close connection and destroy the slave soock
			(void) close(ssock);
		}
		if (FD_ISSET(usock, &rfds)) {
			printf("\a request via UDP \n");
			alen = sizeof(fsin);
			if (recvfrom(usock, buf, sizeof(buf), 0,
				(struct sockaddr *)&fsin, &alen) < 0)
				errexit("recvfrom: %s\n", strerror(errno));
			daytime(buf);
			(void) sendto(usock, buf, strlen(buf), 0,
				(struct sockaddr *)&fsin, sizeof(fsin));
		}
	}
}

int daytime(char buf[])
{
	char	*ctime();
	time_t	time(), now; 

	(void) time(&now);	// get the time
	sprintf(buf, "%s", ctime(&now));  // save the into the buf
}