#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{
	int my_sock, client_sock;
	int bytesArr;
	struct sockaddr_in serverAddr;
	char snd[] = "Hello, this is server";
	char buf[100];

	if ( (my_sock = socket(AF_INET, SOCK_STREAM, 0)) < 0 )
	{
		perror("socket");
		exit(1);
	}

	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(3422);
	serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(my_sock, (struct sockaddr*) &serverAddr, sizeof(serverAddr)) < 0)
	{
		perror("bind");
		exit(1);
	}

	if ( (listen(my_sock, 1)) < 0)
	{
		perror("listen");
		exit(1);
	}

	while ( 1 ) 
	{
		client_sock = accept(my_sock, NULL, NULL);
		if (client_sock != -1)
		{
			while(1)
			{
				bytesArr = recv(client_sock, buf, 100, 0);
				if (bytesArr > 0)
				{
					buf[bytesArr] = '\0';
					printf("this is data from client: %s\n", buf);
					send(client_sock, snd, sizeof(snd), 0);
					break;
				}

			}
			break;
		}	
	}
	
	shutdown(client_sock, 2);
	close(client_sock);

	shutdown(my_sock, 2);
	close(my_sock);
	
	return 0;	
}
