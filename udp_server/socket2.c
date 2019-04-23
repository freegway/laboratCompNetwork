#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>

int main()
{
	int sock;
	struct sockaddr_in myaddr, client;
	char buff[100];
	size_t bytesArr = 0;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		perror("socket");
		exit(1);
	}

	myaddr.sin_family = AF_INET;
	myaddr.sin_port = htons(3422);
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0)
	{
		perror("bind");
		exit(1);
	}


	while (1)
	{
		bytesArr = recvfrom(sock, buff, 100, 0, NULL, NULL);
		if (bytesArr > 0 )
		{
			buff[bytesArr] = '\0';
			printf("this data from socket1: %s\n", buff);
			break;
		}
	}

	client.sin_family = AF_INET;
	client.sin_port = htons(3420);
	client.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	char snd[] = "Hello, this is socket2";
	sendto(sock, snd, sizeof(snd), 0, (struct sockaddr*)&client, sizeof(client));

	shutdown(sock, 2);
	close(sock);
	return 0;
}
