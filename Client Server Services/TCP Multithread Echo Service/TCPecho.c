#include <sys/types.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// include the cource code
#include </afs/pitt.edu/home/f/o/foa5/Echo/connectTCP.c>

extern int errno;

//Defining the prototypes for the functions
int TCPecho(const char *host, const char *service);
int errexit(const char *format, ...);
int connectTCP(const char *host, const char *service);

#define LINELEN 128


//main - TCP clinet for ECHO service

int main(int argc, char *argv[])
{
	char *host = "localhost"; // domine name
	char *service = "echo";   // name the service needed

	switch(argc){
		case 1:
			host = "localhost";
			break;
		case 3:
			service = argv[2]; // if the service given, it will
              		      	           // fall through case 2 and get Domainw Name
		case 2:
			host = argv[1];
			break;
		default:
			fprintf(stderr, "usage: TCPecho [host [port]]\n");
			exit(1);
	}
	TCPecho(host, service);
	exit(0);	// exit successfully

}

// TCPecho - send input to ECHO service on specified host and print reply

int TCPecho(const char *host, const char *service)
{
	char buf[LINELEN+1];
	int s, n;
	int outchars, inchars;

	s = connectTCP(host, service); // make the connection

	while(fgets(buf, sizeof(buf), stdin)){
		buf[LINELEN] = '\0';
		outchars = strlen(buf);
		printf("Just sent the message --> %s \n", buf); 
		(void) write(s, buf, outchars); // sending the request
		printf("\n");

		//read it back
		for(inchars =0; inchars < outchars; inchars+=n) { //reading what sent by the server
			n =read(s, &buf[inchars], outchars - inchars);
			if(n < 0)
			   errexit("socket read failed: %s\n", strerror(errno));
		} 		
		fputs(buf, stdout);
		printf("Just finshed reading the message sent back by the server --> %s\n\n", buf);
	}
}
