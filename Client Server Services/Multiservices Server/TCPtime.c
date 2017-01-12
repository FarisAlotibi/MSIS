
#include <sys/types.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/connectTCP.c>

extern int errno;

#define time_t long 
void TCPtime(const char *host, const char *service);

#define UNIXEPOCH   2208988800UL

//define the errexit prototype
int errexit(const char *format, ...);

//define the connectTCP prototype
int connectTCP(const char *host, const char *service);

#define LINELEN 180

//main - TCP clinet for TIME service

int main(int argc, char *argv[])
{
	char *host = "localhost";// UNIX.CSSD.PITT.EDU
	char *service = "time";


	switch(argc){
		case 1:
				host = "localhost";
				break;
		case 3:
				service = argv[2];// store it here if it was given

		case 2:
				host = argv[1];
				break;
		default:
				fprintf(stderr, "usage: TCPtime [host [port]]\n");
				exit(1);
	}
	TCPtime(host, service);
	exit(0);

}

//TCPtime

void TCPtime(const char *host, const char *service)
{
	int s, n;
	time_t now;	// to store the time

	// make the connections
	s = connectTCP(host, service);
	//Read in a loop because TCP sends in chuncks
	while((n = read(s, (char *)&now, sizeof(now))) > 0){

		now = ntohl((unsigned long)now);
		now -= UNIXEPOCH;
		printf("\nThe EPICH time in seconds is %u \n", now);
		printf("\nThe EPICH time is %s \n", ctime(&now));
		printf("\n");		// new line
	}
}