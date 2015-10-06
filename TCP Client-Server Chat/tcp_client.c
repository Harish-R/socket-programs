/*
  TCP Client-Server Socket Program
  Program: tcp_client.c
  Author: Harish R
*/

#include<stdio.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>

int main()
{
	int sockfd, confd;
	struct sockaddr_in server_addr;
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

	connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  printf("Connected to server\n");

  while(1)
  {
    printf("Client: ");
    fgets(msg, sizeof(msg), stdin);
  	send(sockfd, msg, sizeof(msg), 0);
  	recv(sockfd, msg, sizeof(msg), 0);
    printf("Server: ");
  	puts(msg);
  }

	return 0;
}
