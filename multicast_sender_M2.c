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
	struct sockaddr_in grp;
	struct in_addr lclInterface;
	char buf[1024];
	int blen;

	sck=socket(AF_INET,SOCK_DGRAM,0);
	bzero((char *) &grp, sizeof(grp));
	grp.sin_family = AF_INET;
	grp.sin_addr.s_addr = inet_addr("226.1.2.3");
	grp.sin_port = htons(5435); 

	lclInterface.s_addr =htonl(INADDR_ANY);

	setsockopt(sck, IPPROTO_IP, IP_MULTICAST_IF, (char *)&lclInterface, sizeof(lclInterface));
	blen=sizeof(buf);
	bzero(buf,blen);	
	printf("\nEnter multicast message :");
	fgets(buf,blen,stdin);
	sendto(sck,buf,blen,0, (struct sockaddr*)&grp, sizeof(grp));
		
	return 0;	
}