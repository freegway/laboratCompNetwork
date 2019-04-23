#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	int sock;
	size_t bytesArr;
	struct sockaddr_in serverAddr, myaddr;
	char snd[] = "Hello, this is socket1";
	char buff[100];
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		perror("socket");
		exit(1);
	}
	
	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(3420);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr*)&myaddr, sizeof(myaddr)) < 0)
	{
		perror("bind");
		exit(0);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(3422);
	serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sendto(sock, snd, sizeof(snd), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));

	while(1)
	{
		bytesArr = recvfrom(sock, buff, 100, 0, NULL, NULL);
		if (bytesArr > 0)
		{
			buff[bytesArr] = '\0';
			printf("this data from socket2: %s\n", buff);
			break;
		}
	}
	
	shutdown(sock,2);
	close (sock);

	return 0;

}
