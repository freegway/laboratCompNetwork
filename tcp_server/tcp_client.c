#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	int my_sock;
	struct sockaddr_in serverAddr;
	char snd[] = "Hello, this is client";
	char buf[100];

	if ( (my_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("socket");
		exit(1);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(3422);
	serverAddr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if ( (connect(my_sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr))) < 0)
	{
		perror("connect");
		exit(1);
	}
	
	if ( send(my_sock, snd, sizeof(snd), 0) < 0)
	{
		perror("send");
		exit(1);
	}

	while(1)
	{
		if ( recv(my_sock, buf, 100, 0) > 0 )
		{
			printf("this is data from server: %s\n", buf);
			break;
		}

	}
	

	shutdown(my_sock, 2);
	close(my_sock);
	
	return 0;	
}
