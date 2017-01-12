
#include <sys/types.h>
#include <stdio.h>






#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/connectTCP.c>

#define LINELEN         72


int TCPchargen(const char *host, const char *service);
int errexit(const char *format, ...);
int connectTCP(const char *host, const char *service);

extern int	errno;


/*------------------------------------------------------------------------
 * main - TCP client for DAYTIME service
 *------------------------------------------------------------------------
 */
int main(int argc, char argv[])
{
	

	char *host = "localhost";
	char *service = "chargen";

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
				fprintf(stderr, "usage: TCPecho [host [port]]\n");
				exit(1);
	}
	TCPchargen(host, service);
	exit(0);
}


int TCPchargen(host, service)
char	*host;
char	*service;
{
	int	s, n;			
	int HowMuchToRead;
        char    buf[LINELEN+1];       
        char    *bufptr;

	s = connectTCP(host, service);

    while (1) {

        bufptr = buf;
	HowMuchToRead = sizeof(buf);

	while( (n = read(s, bufptr, HowMuchToRead )) > 0) {
                bufptr += n;
                HowMuchToRead -= n;

	}
        if (n < 0)
		 errexit("socket read failed: %s\n", strerror(errno));
        buf[LINELEN] = '\0'; 
	fputs(buf, stdout);

    }
}