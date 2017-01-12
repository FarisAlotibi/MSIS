//include the passivesock function
//#include </afs/pitt.edu/home/f/o/foa5/Time_Assignment/passivesock.c> //this

//define the passivesock function prototype
//int passivesock(const char *service, const char *transport, int qlen);   // this

//PassiveUDP - create a passive socket fir use in a UDP server
int passiveUDP(const char *service)
{
	return passivesock(service, "udp", 0);
}