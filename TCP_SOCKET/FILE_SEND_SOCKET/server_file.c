#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netdb.h>
#define SIZE 1024
#define port 8080

int main()
{
  char *ip = "127.0.0.1";
  int b,sockfd, new_sock,r;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];
  FILE *fp;
  char *filename = "recv.txt";
  char temp[SIZE];

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

  b = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(b < 0) 
  {
    perror("[-]error in binding socket");
    exit(1);
  }
  printf("[+]socket binding successfull.\n");

  if(listen(sockfd, 10) == 0)
  {
   printf("[+]server is listening....\n");
  }
  else
  {
   perror("[-]server failed to listen");
    exit(1);
  }

  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);
  fp = fopen(filename, "w");
  while (1) 
  {
    r = recv(new_sock, temp, SIZE, 0);
    if (r <= 0)
    {
      break;
    }
    fprintf(fp, "%s", temp);
    bzero(temp, SIZE);
  }
  printf("[+]Data written in the file successfully.\n");
  return 0;
}
