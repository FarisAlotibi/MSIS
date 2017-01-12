#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <sys/wait.h>
#include <sys/errno.h>
#include <netinet/in.h>

// including the source code
#include </afs/pitt.edu/home/f/o/foa5/Echo/passiveTCP.c>

#define QLEN 32
#define BUFSIZE  4096
#define INTERVAL 5

struct { // define group of fields
	pthread_mutex_t	st_mutex;
	unsigned int	st_concount;
	unsigned int	st_contotal;
	unsigned long	st_contime;
	unsigned long	st_bytecount;
} stats;

//define the prototypes
void prstats(void);
int TCPechod(int fd);
int errexit(const char *format, ...);
int passiveTCP(const char *service, int qlen);

//main - Concurrent TCP server for ECHO service

int main(int argc, char *argv[])
{
	
	pthread_t th;
	pthread_attr_t ta;
	char *service ="echo";	
	struct sockaddr_in fsin;
	unsigned int alen;
	int msock; // master socket
	int ssock; // slave socket

	switch(argc) {
		case 1:
			break;
		case 2:
			service = argv[1];
			break;
		default:
			errexit("usage: TCPechod [port]\n");
	}

	msock = passiveTCP(service, QLEN); //make the connection

	(void) pthread_attr_init(&ta);
	(void) pthread_attr_setdetachstate(&ta, PTHREAD_CREATE_DETACHED);
	(void) pthread_mutex_init(&stats.st_mutex, 0);

	if (pthread_create(&th, &ta, (void * (*)(void *))prstats, 0) < 0)
		errexit("pthread_create(prstats): %s\n", strerror(errno));

	while(1) {
		printf("\nWaiting a request from the client \n");
		alen = sizeof(fsin);
		//accepting the request
		ssock = accept(msock, (struct sockaddr *)&fsin, &alen); 
		if(ssock < 0) {
			if(errno == EINTR)
				continue;
			errexit("accept: %s\n", strerror(errno));

		}
		if(pthread_create(&th, &ta, (void * (*)(void *))TCPechod, (void *)ssock) < 0)
			errexit("pthread_create: %s\n", strerror(errno));
	}
}


//TCPechod - echo data unitl end of file

int TCPechod(int fd)
{
	time_t start;
	char buf[BUFSIZE];
	int cc;

	start = time(0);
	(void) pthread_mutex_lock(&stats.st_mutex);
	stats.st_concount++;
	(void) pthread_mutex_unlock(&stats.st_mutex);

	while(cc = read(fd, buf, sizeof buf)) {
		printf("\nJust got the message sent by the client --> %s \n", buf); 
		if(cc < 0)
			errexit("echo read: %s\n", strerror(errno));

		if(write(fd, buf, cc) < 0)
			errexit("echo write: %s\n", strerror(errno));

		(void) pthread_mutex_lock(&stats.st_mutex);
		stats.st_bytecount += cc;
		(void) pthread_mutex_unlock(&stats.st_mutex);
	}
	
	(void) close(fd);
	(void) pthread_mutex_lock(&stats.st_mutex);
	stats.st_contime += time(0) - start;
	stats.st_concount--;
	stats.st_contotal++;
	(void) pthread_mutex_unlock(&stats.st_mutex);
	return 0;
}


//prstats - print server statistical data

void prstats(void){

	time_t now;
	while (1) {
		(void) sleep(INTERVAL);

		(void) pthread_mutex_lock(&stats.st_mutex);
		now = time(0);
		(void) printf("--- %s", ctime(&now));
		(void) printf("%-32s: %u\n", "Current connections",
			stats.st_concount);
		(void) printf("%-32s: %u\n", "Completed connections",
			stats.st_contotal);
		if (stats.st_contotal) {
			(void) printf("%-32s: %.2f (secs)\n",
				"Average complete connection time",
				(float)stats.st_contime /
				(float)stats.st_contotal);
			(void) printf("%-32s: %.2f\n",
				"Average byte count",
				(float)stats.st_bytecount /
				(float)(stats.st_contotal +
				stats.st_concount));
		}
		(void) printf("%-32s: %lu\n\n", "Total byte count",
			stats.st_bytecount);
		(void) pthread_mutex_unlock(&stats.st_mutex);

	}
}































