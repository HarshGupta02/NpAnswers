#include <sys/types.h> 
#include <sys/socket.h> 
#include <netdb.h> 
#include <stdio.h> 
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
int main()
{
	int sck;
	struct sockaddr_in lclSck;
	struct ip_mreq grp;
	struct in_addr lclInterface;
	char buf[1024];
	int reuse = 1;
	int blen;
	sck=socket(AF_INET,SOCK_DGRAM,0);
	
	setsockopt(sck, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse));
	bzero((char *)&lclSck, sizeof(lclSck));
	lclSck.sin_family = AF_INET;
	lclSck.sin_port = htons(5435);
	lclSck.sin_addr.s_addr = INADDR_ANY;

	bind(sck, (struct sockaddr*)&lclSck, sizeof(lclSck));
	grp.imr_multiaddr.s_addr = inet_addr("226.1.2.3");
	grp.imr_interface.s_addr = htonl(INADDR_ANY);
	setsockopt(sck, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&grp, sizeof(grp));
	blen=sizeof(buf);
	bzero(buf,blen);
	read(sck,buf,blen);
	printf("\nMessage from multicast sender is: %s",buf);
	return 0;
}