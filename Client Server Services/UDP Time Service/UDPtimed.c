
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <netinet/in.h>
#include <time.h>
#include <sys/socket.h>

// include the passiveUDP function
#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/passiveUDP.c>

#define UNIXEPOCH   2208988800UL

// cause the pointer points to long, if we have int, we will get warning
#define time_t long 

extern int errno;

//define both errexit and passiveUDP prototype
int errexit(const char *format, ...);
int passiveUDP(const char *service);


//main - UDP clinet for TIME service
int main(int argc, char *argv[])
{
	// sockaddr_in entity
	struct sockaddr_in fsin;
	char *service = "time";
	char buf[1];
	int sock;
	time_t now; // to store the time

	unsigned int alen;

	switch(argc) {
		case 1:
			break;
		case 2:
			service = argv[1];
			break;
		default:
			errexit("usage: UDPtimed [port]\n");
	}
	// call passiveUDP function
	sock = passiveUDP(service);

	while(1)
	{
	  alen = sizeof(fsin);
	  if(recvfrom(sock, buf, sizeof(buf), 0,(struct sockaddr *)&fsin, &alen) < 0)
		errexit("recvfrom: %s\n", strerror(errno));
	  (void) time(&now); // get the time
	  now = htonl((unsigned long)(now + UNIXEPOCH));

	  (void) sendto(sock, (char *)&now, sizeof(now), 0,
		 (struct sockaddr *)&fsin, sizeof(fsin));
	}
}







