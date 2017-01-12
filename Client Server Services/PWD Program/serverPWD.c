#include <stdio.h>      // library included to use ferror, fprintf, printf, and BUFSIZ
#include <sys/types.h>  // library included to use the datatypes such as char
#include <sys/socket.h> // library included to use accept, bind, and listen functions
#include <netinet/in.h> // library included to use sockaddr_in structure
#include <netdb.h>      // library included to use hostent and servent structures
#include <pwd.h>		// library included to use passwd structure
//-----------------------------------------changes
#include <strings.h>    //included to execute strlen, strcpy, bcopy methods
#include <unistd.h>     //included to execute read, write, close, gethostname methods
#include <stdlib.h>     //included to execute exit() method
/*

program: whoisServer

Purpose: UNIX application program acts as a server for the whois service
         and listens on well known whois port.

Use of Client: whois hostname username

Auther: Faris Alotibi

Date: September, 2016

*/

#define BACKLOG 5            // constant for number of requests to queue
#define MAXHOSTNAME 32       // maximum length of host name 
void whois(int sock);        // Method initialization
unsigned short portbase = 0; // Initialized variable to be used ..
							 // for raising the port number to user level

void main(argc, argv)        // Declaration of the main type as void
int argc;                    // declaring unix arguments
char *argv[];
{
	int s, t;                    //socket descriptors
	int i;                       // general integer used in the program
	struct sockaddr_in sa, isa;  //Internet socket address structure (group of fields) includes ..
                         		 //sin_family, port, addr, and zero 
								 //using 2 internet socket address structure ..
								 // one for accepting the request and ..
								 // second one does the request

	struct hostent *hp;          //host name lookup result includes name of the host,  ..
                        		 //alter names, host address type length in bytes of ..
                         		 //each address, vector of addresses for the host, and ..
                                 //first host address

	char *myname;                //pointer points to the program name entered by the user
	struct servent *sp;          //service lookup result includes name of the service, ..
                         		 //alter services names, port num., and protocol name
	char localhost[MAXHOSTNAME+1];  //local host name as character string and the one for null

	myname = argv[0];		// store the program name
	portbase = 8002;        //to raise the port number to the user level instead of 
							//the privilaged level,Kernel.

	// look up the whois service entry with the TCP connection
	if((sp = getservbyname("whois","tcp")) == NULL) {
		fprintf(stderr, "%s: No whois service on this host \n", myname);
		exit(1);		// sends 1 in case error occurs
	}

	// Get out own host information
	gethostname(localhost, MAXHOSTNAME);  // localhost is the generic
	if((hp = gethostbyname(localhost)) == NULL){	// look up the specified hostname and get its IP ..
                                                    // and stored its info into the hostent members
		fprintf(stderr, "%s: cannot get local host info? \n", myname);// print out in case of error occurs
		exit(1);
	}
	//into the socket structure, aut the WHOIS socket number and our address information 
	// Convert from network to host representation and increase port value
	// to do the arithmatic and convert it back
	sa.sin_port = htons(ntohs((unsigned short) sp->s_port) + portbase);
	//Into socket structure, add the host's IP address and address type
	bcopy((char *)hp->h_addr, (char *)&sa.sin_addr, hp->h_length);
	// assigning the addrtype into the family member in the socket
	sa.sin_family = hp->h_addrtype;

    // Allocate an open socket by calling socket function and passing the 
    // host address type
	if((s = socket(hp->h_addrtype, SOCK_STREAM, 0)) < 0) {
		perror("socket");
		exit(1);
	}

	//printing the socket value
	printf("This is the socket value %d \n", s);


	//to hear incoming connections, we blind the socket to the service port 
	if(bind(s,(struct sockaddr *)&sa, sizeof sa) < 0){   // Casting to sockaddr
		perror("bind");
		exit(1);
	}
	//Set the maximum connections and start listening
	listen(s, BACKLOG);

	//make the server goes into an infinite loop waiting for new connections
	while(1){ // waiting for ever
		i = sizeof isa;
		// print msg indicating that we are waiting the request
		printf("\nWaiting Client request :)\n");
        //We are blocking here waiting for new customers
		// accept the request
        if((t = accept(s, (struct sockaddr *)&isa,&i)) < 0){   // Casting to sockaddr
        	perror("accept");
        	exit(1);
        }
        whois(t);     //perform the whois service
        close(t);	  // close the socket
	}
}


void whois(sock)  //Get the whois request from remots host and form a reply
int sock;
{
	struct passwd *p;	// structure includes user's login name, numerical user ID, ..
						// numerical group ID, initial working directory, ..
						// and program to use as shell
	char buf[BUFSIZ+1];
	int i;
	printf("\nWhois Service Started\n"); // print msg once Whois service starts

	//Get one line request
	if(( i = read(sock, buf, BUFSIZ)) <= 0)
		return;
	buf[i] = '\0';     //gets null to terminate
	// print the username the server is asking about
	printf("\nThis is the username %s being searched for\n", buf); 
	//Look up the requested user and form a reply
	if((p = getpwnam(buf)) == NULL)	// get password name
		strcpy(buf, "User not found\n"); 
	else
		//the user idntification number is being sent as well as the group ID
		// and the initial working directory as well as the shell
		// formate it to buffer
	    sprintf(buf, "User: %s \n Full Name: %s \n  UID: %d \n  GID: %d \n Dir: %s \n Shell: %s \n ",
		p->pw_name, p->pw_gecos, p->pw_uid, p->pw_gid, p->pw_dir, p->pw_shell); 

	//Return the reply to the client
    write(sock, buf, strlen(buf));
    // notification that the result was sent
    printf("\nThe result was sent to the client\n");
    return;  // return to the caller
}

