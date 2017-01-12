

#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/passivesock.c>


int passivesock(const char *service, const char *transport, int qlen);

/*

PassiveTCP - create a passive socket for use in a TCP server

*/

int
passiveTCP(const char *service, int qlen)
{
	return passivesock(service, "tcp", qlen);
}