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
	struct sockaddr_in servaddr,cliaddr;
	char buffer[100];
	
	listenfd=socket(AF_INET,SOCK_DGRAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=htons(22000);
	servaddr.sin_addr.s_addr=inet_addr("192.168.29.255");
	int en=1;
	int ret=setsockopt(listen_fd,SOL_SOCKET,SO_BROADCAST,&en,sizeof(en));
	int len=(sizeof(cliaddr));
	bzero(buffer,100);
	strcpy(buffer,"hello");
	sendto(listenfd,buffer,strlen(buffer),MSG_CONFIRM,(struct sockaddr*)&servaddr,sizeof(servaddr));
	printf("message sent");
	close(listenfd);
}