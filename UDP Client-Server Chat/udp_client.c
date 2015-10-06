/*
  UDP Client-Server Socket Program
  Program: udp_client.c
  Author: Harish R
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;

int main()
{
  int sockfd;
  char msg[100];
  sockaddr_in this_addr, server_addr, client_addr;
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  if(sockfd == -1)
  {
    printf("Failed to create socket.\n");
    return -1;
  }
  this_addr.sin_family = AF_INET;
  this_addr.sin_port = htons(1112);
  this_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  int b = bind(sockfd, (sockaddr*)&this_addr, sizeof(this_addr));
  if(b == -1)
  {
    printf("Failed to bind");
    return -1;
  }
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(1111);
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  int server_addr_len = sizeof(server_addr);

  while(1)
  {
    printf("Client: ");
    fgets(msg, sizeof(msg), stdin);
    sendto(sockfd, msg, sizeof(msg), 0, (sockaddr*)&server_addr, sizeof(server_addr));
    recvfrom(sockfd, msg, sizeof(msg), 0, (sockaddr*)&server_addr, &server_addr_len);
    printf("Server: ");
    puts(msg);
  }

  close(sockfd);
  return 0;
}
