
#include <sys/types.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/connectTCP.c>
//#include <errexit.c>


extern int errno;

void TCPdaytime(const char *host, const char *service);
int errexit(const char *format, ...);
int connectTCP(const char *host, const char *service);

#define LINELEN 128

/*
	main - TCP clinet for DAYTIME service
*/

int main(int argc, char *argv[])
{
	char *host = "localhost";
	char *service = "daytime";

	switch(argc){
		case 1:
				host = "localhost";
				break;
		case 3:
				service = argv[2];

		case 2:
				host = argv[1];
				break;
		default:
				fprintf(stderr, "usage: TCPdaytime [host [port]]\n");
				exit(1);
	}
	TCPdaytime(host, service);
	exit(0);

}

/*
	TCPdaytime

*/

void TCPdaytime(const char *host, const char *service)
{
	char buf[LINELEN+1];
	int s, n;

	s = connectTCP(host, service);

	while((n = read(s, buf, LINELEN)) > 0){
		buf[n] = '\0';
		(void) fputs(buf, stdout);
	}
}












