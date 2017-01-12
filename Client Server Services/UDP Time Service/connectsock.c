#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

//include the errexit source code using the path
#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/errexit.c>

#ifndef INADDR_NONE
#define INADDR_NONE 0xffffffff //any address will be accepted
#endif /* INADDR_NONE */

extern int errno;

//prototype for the errexit function
int errexit(const char *format, ...);

// Portbase, for non privilged level
unsigned short portbase = 0;  

// connectsock function,  using TCP or UDP to allocate & connect a socket

int connectsock(const char *host, const char *service, const char *transport)
{
	// a pointer to host entity
	struct hostent *phe; 		
	// a pointer to service entity
	struct servent *pse; 		
	// pointer to protocol entity
	struct protoent *ppe; 		
	// an internet endpoint address
	struct sockaddr_in sin; 	
	// scoket descriptor and socket type
	int s, type;				

	// set some value intp the memory
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;


	// assign the prot number
	portbase = 8022;   


	// Map service name to port number 
	if(pse = getservbyname(service,transport)){
		// do the conversion from network to host and vice versa and add port#
		printf("\nService port is %d\n", pse->s_port);
		sin.sin_port = htons(ntohs((unsigned short)pse->s_port)+portbase);
	}
	else if((sin.sin_port=htons((unsigned short)atoi(service))) == 0)
		errexit("can't get \"%s\" service entry\n",service);


	// Map host name to IP address, allowing for dotted decimal 
	if(phe = gethostbyname(host))
		//like bcopy function
		memcpy(&sin.sin_addr, phe->h_addr, phe->h_length);
	else if((sin.sin_addr.s_addr = inet_addr(host)) == INADDR_NONE)
		errexit("can't get \"%s\" host entry\n", host);


	// Map transport protocol name to protocol number 
	if((ppe = getprotobyname(transport)) == 0)
		errexit("can't get \"%s\" protocol entry\n ", transport);

	// Use protocol to choose a socket type
	if(strcmp(transport, "udp") == 0)
		type = SOCK_DGRAM;
	else if(strcmp(transport, "tcp") == 0)
		type = SOCK_STREAM;
	else
		printf("Transport was not specified\n");

	// Allocate a socket 
	s = socket(PF_INET, type, ppe->p_proto);
	if(s < 0)
		errexit("can't create socket: %s\n", strerror(errno));

	// Connect the socket 
	if(connect(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errexit("can't connect to %s,%s: %s\n", host, service, strerror(errno));
	return s;



}