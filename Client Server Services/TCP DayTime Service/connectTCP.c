// include the connectsock function
#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/connectsock.c>

//the connectsock prototype
int connectsock(const char *host, const char *service, const char *transport);

int connectTCP(const char *host, const char *service)
{
	return connectsock(host, service, "tcp");
}