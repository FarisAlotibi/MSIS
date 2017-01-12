
#include <sys/types.h>

#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/connectTCP.c>

extern int errno;

void TCPdaytime(const char *host, const char *service);

//define the errexit prototype
int errexit(const char *format, ...);

//define the connectTCP prototype
int connectTCP(const char *host, const char *service);

#define LINELEN 180

//main - TCP clinet for DAYTIME service

int main(int argc, char *argv[])
{
	char *host = "localhost";// UNIX.CSSD.PITT.EDU
	char *service = "daytime";

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
				fprintf(stderr, "usage: TCPdaytime [host [port]]\n");
				exit(1);
	}
	TCPdaytime(host, service);
	exit(0);

}

//TCPdaytime

void TCPdaytime(const char *host, const char *service)
{
	char buf[LINELEN+1];
	int s, n;
	int cont = 0;	//counter to distinguish
	// make the connections
	s = connectTCP(host, service);
	//Read in a loop because TCP sends in chuncks
	while((n = read(s, buf, LINELEN)) > 0){
		buf[n] = '\0';
		if(cont == 0)
			printf("\nTime in USA\n");	// print label			
		else if (cont == 1)
			printf("\nTime in Saudi Arabia\n");	//print label
		cont++;		
		(void) fputs(buf, stdout);
		printf("\n");		// new line
	}
}












