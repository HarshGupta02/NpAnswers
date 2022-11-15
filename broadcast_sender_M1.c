#include <stdio.h>      /* for printf() and fprintf() */
#include <sys/socket.h> /* for socket() and bind() */
#include <arpa/inet.h>  /* for sockaddr_in */
#include <stdlib.h>     /* for atoi() and exit() */
#include <string.h>     /* for memset() */
#include <unistd.h>     /* for close() */
#include <netinet/in.h>

int main(int argc, char *argv[])
{
    int sock;                         /* Socket */
    struct sockaddr_in broadcastAddr; /* Broadcast address */
    char *broadcastIP;                /* IP broadcast address */
    unsigned short broadcastPort;     /* Server port */
    char *sendString;                 /* String to broadcast */
    int broadcastPermission;          /* Socket opt to set permission to broadcast */
    unsigned int sendStringLen;       /* Length of string to broadcast */


    broadcastIP = "192.168.108.20";   /* First arg:  broadcast IP address */ 
    broadcastPort = 8080;    /* Second arg:  broadcast port */
    sendString = "Hello from server!\n";             /* Third arg:  string to broadcast */

    /* Create socket for sending/receiving datagrams */
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
    {
		printf("Error while creating socket.\n");
		exit(EXIT_FAILURE);
	}

    /* Set socket to allow broadcast */
    broadcastPermission = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (void *) &broadcastPermission, sizeof(broadcastPermission)) < 0)
    {
		printf("Error while setting socket option.\n");
		exit(EXIT_FAILURE);
	}

    /* Construct local address structure */
    memset(&broadcastAddr, 0, sizeof(broadcastAddr));   /* Zero out structure */
    broadcastAddr.sin_family = AF_INET;                 /* Internet address family */
    broadcastAddr.sin_addr.s_addr = inet_addr(broadcastIP);/* Broadcast IP address */
    broadcastAddr.sin_port = htons(broadcastPort);         /* Broadcast port */

    sendStringLen = strlen(sendString);  /* Find length of sendString */
    for (;;) /* Run forever */
    {
         /* Broadcast sendString in datagram to clients every 3 seconds*/
         if (sendto(sock, sendString, sendStringLen, 0, (struct sockaddr *) 
               &broadcastAddr, sizeof(broadcastAddr)) != sendStringLen)
        {
			printf("Error while sending message.\n");
			exit(EXIT_FAILURE);
		}

        sleep(3);   /* Avoids flooding the network */
    }
    /* NOT REACHED */
}

