
#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/connectUDP.c>

#define BUFSIZE 400

#define UNIXEPOCH   2208988800UL
#define MSG		"what time is it?\n"
//define time_t as long because the ctime returns now vari. with long type
#define time_t long 

extern int errno;

//define the errexit prototype
int errexit(const char *format, ...);

//define the connectUDP prototype
int connectUDP(const char *host, const char *service);

//main - UDP clinet for TIME service

int main(int argc, char *argv[])
{
	char *host = "localhost"; // UNIX.CSSD.PITT.EDU
	char *service = "time";
	time_t now;	// to store the time
	int s, n;

	switch(argc){
		case 1:
				host = "localhost";
				break;
		case 3:
				service = argv[2]; // store it here if it was given

		case 2:
				host = argv[1];
				break;
		default:
				fprintf(stderr, "usage: UDPtime [host [port]]\n");
				exit(1);
	}
	
	// make the connections
	s = connectUDP(host, service);
	
	// request
	(void) write(s, MSG, strlen(MSG));

	//Read the time

	n = read(s, (char *)&now, sizeof(now));
	if(n < 0)
		errexit("read failed: %s\n", strerror(errno));
	now = ntohl((unsigned long)now);
	printf("\nThe UCT time is %u \n", now);
	now -= UNIXEPOCH;
	//print the machine time formate
	printf("\nThe time after UNIX epoch conversion is %u \n", now);
	
	//print the readable time formate
	printf("%s\n", ctime(&now));

	exit(0);
	

}

