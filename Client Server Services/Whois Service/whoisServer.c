#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <pwd.h>
//-----------------------------------------changes
#include <strings.h>            //included to execute strlen, strcpy, bcopy methods
#include <unistd.h>       	//included to execute read, write, close, gethostname methods 
#include <stdlib.h>		//included to execute exit() method
/*

program: whoisServer

Purpose: UNIX application program acts as a server for the whois service 
         and listens on well known whois port.

Use of Client: whois hostname username

Auther: Faris Alotibi

Date: September, 2016

*/

#define BACKLOG 5                       // number of requests to queue
#define MAXHOSTNAME 32                  // maximum host name length
void whois(int sock);                   // Method initialization
unsigned short portbase = 0;            // Initialized variable to be used for raising the port number to user level

void main(argc, argv)                   // Declaration of the main type as void
int argc;                               //standard unix argument declaration
char *argv[];
{
	int s, t;                       //socket descriptors
	int i;                          // general integer
	struct sockaddr_in sa, isa;     //internet socket address structure
	struct hostent *hp;             //result of host name lookup
	char *myname;                   //pointer to name of this program
	struct servent *sp;             //result of service lookup
	char localhost[MAXHOSTNAME+1];  //local host name as character string

	myname = argv[0];
	portbase = 8002;        //to raise the port number to the user level instead of the privilaged level,Kernel.

        // look up the whois service entry
	if((sp = getservbyname("whois","tcp")) == NULL) {
		fprintf(stderr, "%s: No whois service on this host \n", myname);
		exit(1);
	}

	// Get out own host information

	gethostname(localhost, MAXHOSTNAME);
	if((hp = gethostbyname(localhost)) == NULL){
		fprintf(stderr, "%s: cannot get local host info? \n", myname);
		exit(1);
	}

	//Put the WHOIS socket number and our address information into the socket structure
	// Convert from host to network representation and increase port value
	sa.sin_port = htons(ntohs((unsigned short) sp->s_port) + portbase);    
	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	sa.sin_family = hp->h_addrtype;

	// Allocate an open socket for incoming connections

	if((s = socket(hp->h_addrtype, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}
        
	
        //Blind the socket to the service port so we hear incoming connections
	if(bind(s,(struct sockaddr *)&sa, sizeof sa) < 0){   // Casting to sockaddr
		perror("bind");
		exit(1);
	}
        
        //Set maximum connections we will fall behind
	listen(s, BACKLOG);
        
        //Go into an infinite loop waiting for new connections
	while(1){
		i = sizeof isa;
		printf("\nWaiting Client request :)\n");
                //We hang in accept() while waiting for new customers
		if((t = accept(s, (struct sockaddr *)&isa,&i)) < 0){   // Casting to sockaddr
			perror("accept");
			exit(1);
		}
		whois(t);     //perform the actual whois service
		close(t);
	}  
}
//Get the whois request from remots host and format a reply

void whois(sock)
int sock;
{
        struct passwd *p;
        char buf[BUFSIZ+1];
        int i;
	printf("\nWhois Service Started\n");

        //Get one line request
        if(( i = read(sock, buf, BUFSIZ)) <= 0)
                return;
        buf[i] = '\0';     //Null terminate
	printf("\nThis is the username %s being searched for\n", buf);
        //Look up the requested user and format reply
        if((p = getpwnam(buf)) == NULL)
                strcpy(buf, "User not found\n");
        else
                sprintf(buf, "%s: %s The UID: %d The GID: %d \n My initial: %s ",
		 p->pw_name, p->pw_gecos, p->pw_uid, p->pw_gid, "FARIS");
		  //the user idntification number is being sent

        //Return reply
        write(sock, buf, strlen(buf));
	printf("\nThe result was sent to the client\n");
        return;
}

