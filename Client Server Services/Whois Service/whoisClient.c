/*whois.c - main */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
//-------------------------------------- changes
#include <stdlib.h>              //included to execute exit() method
#include <strings.h>             //included to execute strlen, bcopy methods 
#include <unistd.h>              //included to execute read, write, close, gethostname methods
/*
program: whoisClient

Purpose: UNIX application program acts as a client for the whois service.

Use of Client: whois hostname username

Auther: Faris Alotibi

Date: September, 2016
*/
unsigned short portbase = 0;     //initialized variable to be used for raising the port number to user level
void main(argc, argv)            // Declaration of the main type as void
int argc;
char *argv[];
{
  int s;                          //socket descriptor
  int len;                        //length of received data
  struct sockaddr_in sa;          //Internet socket addr. structure
  struct hostent *hp;             //result of host name lookup
  struct servent *sp;             //result of service lookup
  char buf[BUFSIZ+1];             //buffer to read whois information
  char *myname;                   //pointer to name of this program
  char *host;                     //pointer to remote host name
  char *user;                     //pointer to remote user name
  
  myname = argv[0];
  /*
  check that there are two command line arguments
  */
  if(argc !=3){
    fprintf(stderr, "Usage: %s host username\n", myname);
    exit(1);
  }
  host = argv[1];
  user = argv[2];
  
  // look up the specified hostname
  if ((hp = gethostbyname(host)) == NULL) {
    fprintf(stderr, "%s: %s: no such host?\n", myname, host);
    exit(1);
  }
  
  // Put host's address and address type into socket structure
  bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);     
  sa.sin_family = hp->h_addrtype;
  
  portbase = 8002;     //to raise the port number to the user level instead of the privilaged level,Kernel.
  
  // look up the socket number for the WHOIS service
  if((sp = getservbyname("whois", "tcp")) == NULL) {
    fprintf(stderr, "%s: No whois service on this host\n", myname);
    exit(1);
  }
  
  //Put the whois socket number into the socket structure.
  // Convert from host to network representation and increase port value
  sa.sin_port = htons(ntohs((unsigned short)sp->s_port)+portbase);      
  // Allocate an open socket
  if((s = socket(hp->h_addrtype, SOCK_STREAM, 0)) <0 ) {
    perror("socket");
    exit(1);
  }
  
  //Connect to the remote server
  if(connect(s,(struct sockaddr *) &sa, sizeof sa) < 0) {    // Casting to sockaddr
    perror("connect");
    exit(1);
  }
  
  //Send the request
  if(write(s, user, strlen(user)) != strlen(user)) {
    fprintf(stderr, "%s: write error\n", myname);
    exit(1);
  }
  
  while((len = read(s, buf, BUFSIZ)) >0){
	printf("\nGetting the Response from the Server\n");
  	write(1, buf, len);
  }
  close(s);
  exit(0);
  
  
}

