
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/superd.c>


#define	BUFFERSIZE	4096

extern int errno;

void TCPechod(int), TCPchargend(int), TCPdaytimed(int), TCPtimed(int);
int	errexit(const char *format, ...);


/*
	TCPecho
*/

void TCPechod(int fd)
{
	printf("\n Echo Service \n");
	char	buf[BUFFERSIZE];
	int	cc;

	while (cc = read(fd, buf, sizeof buf)) {
		if (cc < 0)
			errexit("echo read: %s\n", strerror(errno));
		printf("\n Message recieved and was forwarded back %s \n", buf);
		if (write(fd, buf, cc) < 0)
			errexit("echo write: %s\n", strerror(errno));
	}
}

#define	LINELEN	72

/*
	TCPchargend
*/

void TCPchargend(int fd)
{
	printf("\n Character Generator Service \n");
	char c, buf[LINELEN+2];	
	c = ' ';
	buf[LINELEN] = '\r';
	buf[LINELEN+1] = '\n';
	while (1) {
		int	i;
		for (i=0; i<LINELEN; ++i) {
			buf[i] = c++;
			if (c > '~')
				c = ' ';
		}
		if (write(fd, buf, LINELEN+2) < 0)
			break;
	}
}


/*
	TCPdaytimed
*/


void TCPdaytimed(int fd){
	printf("\n Daytime Service \n");
	char buf[LINELEN], *ctime();
	time_t	now;

	(void) time(&now);
	sprintf(buf, "%s", ctime(&now));
	(void) write(fd, buf, strlen(buf));
}

#define UNIXEPOCH 2208988800UL


/*
	TCPtimed
*/

void TCPtimed(int fd)
{	
	printf("\n Time Service \n");
	time_t	now;

	(void) time(&now);
	now = htonl((unsigned long)(now + UNIXEPOCH));
	(void) write(fd, (char *)&now, sizeof(now));
}















