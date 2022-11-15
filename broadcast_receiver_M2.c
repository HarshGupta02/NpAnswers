#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include<string.h>

int main()
{
	int listenfd;
	struct sockaddr_in servaddr,recvaddr;
	char buffer[100];
	
	bzero(&servaddr,sizeof(servaddr));
	listenfd=socket(AF_INET,SOCK_DGRAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(22000);
	servaddr.sin_addr.s_addr=inet_addr("192.168.29.255");
	
	bind(listenfd,(const struct sockaddr *)&servaddr,sizeof(servaddr));
	
	bzero(buffer,100);
	int len=(sizeof(recvaddr));
	recvfrom(listenfd,buffer,1024,MSG_WAITALL,(struct sockaddr*)&recvaddr,len);
	printf("server:%s",buffer);
	close(listenfd);
}