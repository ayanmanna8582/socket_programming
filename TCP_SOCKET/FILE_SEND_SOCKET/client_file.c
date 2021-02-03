#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#define SIZE 1024
#define port 8080

int main()
{
  char *ip = "127.0.0.1";
  int sockfd,conn,n;  
  char data[SIZE] = {0};
  struct sockaddr_in server_addr;
  FILE *fp;
  char *filename = "send.txt";
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) 
  {
    perror("[-]socket creation failed");
    exit(1);
  }
  printf("[+]socket created successfully.\n");

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);

  conn = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(conn == -1) 
  {
    perror("[-]socket connection failed");
    exit(1);
  }
 printf("[+]connected to Server .\n");

  fp = fopen(filename, "r");
  if (fp == NULL) 
  {
    perror("[-]couldn't  read file.");
    exit(1);
  }


  while(fgets(data, SIZE, fp) != NULL) 
  {
    if (send(sockfd, data, sizeof(data), 0) == -1) 
    {
      perror("[-]couldn't send file.");
      exit(1);
    }
    bzero(data, SIZE);
  }
  printf("[+]data sent successfully.\n");
  printf("[+]connection is closed.\n");
  close(sockfd);
  return 0;
}
