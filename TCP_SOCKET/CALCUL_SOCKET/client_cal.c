#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h> 
#include <unistd.h>
#include<string.h> 
#include<strings.h>
#include <arpa/inet.h>
#define PORT 8080

int main()
{
  int sockfd,size,conn;
  char operator;
  int operand1,operand2;
  float result;
  if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
   printf("[+]Socket created sucessfully\n");
  else
   perror("[-]Socket creation failed"); 

  struct sockaddr_in servaddr;
  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  servaddr.sin_port=PORT;

  size = sizeof(struct sockaddr_in);
  if((conn=connect(sockfd,(struct sockaddr *) &servaddr, size))==0)
   printf("[+]Connection successfull\n");
  else
   perror("[-]couldn't connect");

  printf("[+]Now choose and enter an operator given below:----\n");
  printf(" (1): '+' for 'addition' \n (2): '-' for 'subtraction' \n (3): '*' for 'multiplication' \n (4): '/' for 'division' \n Operand:");

  scanf("%c",&operator);
  printf("Enter two operands now:\n");
  scanf("%d %d", &operand1, &operand2);

  write(sockfd,&operator,10);
  write(sockfd,&operand1,sizeof(operand1));
  write(sockfd,&operand2,sizeof(operand2));
  read(sockfd,&result,sizeof(result)); 
  printf("Result got from server is : %.2f\n",result);  
  close(sockfd);
  return 0;
}
