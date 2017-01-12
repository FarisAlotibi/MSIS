/*whois.c - main */
#include <stdio.h>      // library included to use ferror, fprintf, printf, and BUFSIZ
#include <sys/types.h>  // library included to use the datatypes such as char
#include <sys/socket.h> // library included to use accept, bind, and connect functions
#include <netinet/in.h> // library included to use sockaddr_in structure
#include <netdb.h>      // library included to use hostent and servent structures
//-------------------------------------- changes
#include <stdlib.h>   //included to execute exit() method
#include <strings.h>  //included to execute strlen, bcopy methods
#include <unistd.h>   //included to execute read, write, close, gethostname methods
/*
program: whoisClient

Purpose: UNIX application program acts as a client for the whois service.

Use of Client: whois hostname username

Auther: Faris Alotibi

Date: September, 2016
*/
unsigned short portbase = 0; //initialized variable to be used for raising  ..
                             //the port number to the uprotected area
void main(argc, argv)        // Declaration of the main type as void
int argc;
char *argv[];
{
  int s;                 //socket descriptor
  int len;               //length of data beng received
  struct sockaddr_in sa; //Internet socket address structure (group of fields) includes ..
                         //sin_family, port, addr, and zero 

  struct hostent *hp;    //host name lookup result includes name of the host,  ..
                         //alter names, host address type length in bytes of ..
                         //each address, vector of addresses for the host, and ..
                         //first host address

  struct servent *sp;    //service lookup result includes name of the service, ..
                         //alter services names, port num., and protocol name
  char buf[BUFSIZ+1];    //whois information read by this buffer
  char *myname;          //pointer points to the program name entered by the user
  char *host;            //pointer points to the name of remote host entered by the user
  char *user;            //pointer points to the remote username entered by the user

  myname = argv[0];      // store the program name


  if(argc !=3){  // Make sure that three arguments are entered (the executable + host + username) 
    fprintf(stderr, "Usage: %s host username\n", myname);
    exit(1);          // error in case the entry was less than the required
  }
  host = argv[1];     // store the host or place entered
  user = argv[2];     // store the username entred

  if ((hp = gethostbyname(host)) == NULL) {   // look up the specified hostname and get its IP ..
                                              // and stored its info into the hostent members
    fprintf(stderr, "%s: %s: no such host?\n", myname, host); // print out in case of error occurs
    exit(1);
  }
  //Into socket structure, add the host's IP address and address type 
  bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);   
  // assigning the addrtype into the family member in the socket
  sa.sin_family = hp->h_addrtype;                                  

  //to increase the port number to the unprotected level instead of the privilaged level,Kernel.
  portbase = 8002;     

  // look up the socket number for the WHOIS service and store its info ..
  // into the servent structure members
  if((sp = getservbyname("whois", "tcp")) == NULL) {                                             
    fprintf(stderr, "%s: No whois service on this host\n", myname);
    exit(1);
  }

  //Into socket structure, add the whois socket number
  // Convert from network to host representation and increase port value
  // to do the arithmatic and convert it back
  sa.sin_port = htons(ntohs((unsigned short)sp->s_port)+portbase);
  // Allocate an open socket by calling socket function and passing the 
  // host address type
  if((s = socket(hp->h_addrtype, SOCK_STREAM, 0)) <0 ) {
    perror("socket");
    exit(1);
  }

  //Connect to the remote server using connect function and passing ..
  // the socket, address and the size 
  if(connect(s,(struct sockaddr *) &sa, sizeof sa) < 0) {    // Casting to sockaddr
    perror("connect");
    exit(1);
  }

  //Send the request using write function by passing socket, ..
  //username, and its length and check if the server wrote
  //the same one
  if(write(s, user, strlen(user)) != strlen(user)) {
    fprintf(stderr, "%s: write error\n", myname);
    exit(1);
  }
  //since TCP sends the msg in pieces we need while to read it
  //here we read
  while((len = read(s, buf, BUFSIZ)) >0){ // we handle the msg.
    //print msg. once we get values from the server
    printf("\nGetting the Response from the Server\n"); 
    write(1, buf, len); //used 1 for the standard display .. show the values
  }
  
  close(s);  // close the socket
  exit(0);   // exit successfully


}
