#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <string.h>
#include <stdlib.h>

//include the errexit function
#include </afs/pitt.edu/home/f/o/foa5/Echo/errexit.c> 

extern int errno;

//errexit function prototype
int errexit(const char *format, ...);

// port base, for non-privilged level
unsigned short portbase = 0;  

//passivesock - using TCP or UDP to allocate & bind a server socket 

int passivesock(const char *service, const char *transport, int qlen)
{
	// a pointer to service entity
	struct servent *pse; 		
	// pointer to protocol entity
	struct protoent *ppe; 		
	// an internet endpoint address
	struct sockaddr_in sin; 	
	// scoket descriptor and socket type
	int s, type;				
	
	// set some value into the memory
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	// ANY ADDRESS accepts
	sin.sin_addr.s_addr = INADDR_ANY;

	// a well-known port numner 
	portbase = 8022; 


	// Map service name to port number 
	if(pse = getservbyname(service,transport))
		//do the conversion from the network to host and vice versa
		sin.sin_port = htons(ntohs((unsigned short)pse->s_port)+portbase);
	else if((sin.sin_port=htons((unsigned short)atoi(service))) == 0)
		errexit("can't get \"%s\" service entry\n",service);


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

	// Bind the socket 
	if(bind(s, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		errexit("can't bind to %s port: %s\n", service, strerror(errno));
	if(type == SOCK_STREAM && listen(s, qlen) < 0)
		errexit("can't listen on %s port: %s\n", service, strerror(errno));

	return s;


}