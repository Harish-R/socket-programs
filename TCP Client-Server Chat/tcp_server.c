/*
  TCP Client-Server Socket Program
  Program: tcp_server.c
  Author: Harish R
*/

#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main()
{
	int sockfd, confd;
	struct sockaddr_in server_addr, client_addr;
	char msg[100];
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd == -1)
  {
    perror("Cannot create socket...\n");
    return -1;
  }
  else
    printf("TCP Socket created\n");

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(4444);
	server_addr.sin_addr.s_addr = INADDR_ANY;
	int b = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(b == -1)
  {
    perror("Error binding to port...\n");
    return -1;
  }
  else
    printf("Bound to port 4444\n");

	int client_size = sizeof(client_addr);

  printf("Listening for connection...\n");
	listen(sockfd, 5);
	confd = accept(sockfd, (struct sockaddr*)&client_addr, &client_size);
  if (confd == -1)
  {
    perror("Failed to accept connection\n");
    return -1;
  }
  else
    printf("Accepted connection from client.\n");

	while(1)
	{
		recv(confd, msg, sizeof(msg), 0);
    printf("Server: ");
    puts(msg);
    printf("Client: ");
		fgets(msg, sizeof(msg), stdin);
		send(confd, msg, sizeof(msg), 0);
	}

	return 0;
}
