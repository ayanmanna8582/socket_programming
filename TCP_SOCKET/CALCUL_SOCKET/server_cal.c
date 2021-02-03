#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<netinet/in.h> 
#include <unistd.h>
#include<string.h> 
#include <arpa/inet.h>
#define PORT 8080

int main()
{
  int sockfd,connfd,size;
  char operator;
  int operand1,operand2;
  float result;
  if((sockfd=socket(AF_INET,SOCK_STREAM,0))>0)
   printf("[+]Socket created sucessfully\n");
  else
   perror("[-]Socket creation failed"); 

  struct sockaddr_in servaddr;              
  struct sockaddr_in cliaddr;

  servaddr.sin_family=AF_INET;
  servaddr.sin_addr.s_addr=inet_addr("127.0.0.1");
  servaddr.sin_port=PORT;

  if((bind(sockfd, (struct sockaddr *)&servaddr,sizeof(servaddr)))==0)
   printf("[+]Bind sucessful\n");
  else
   perror("[-]Problem found in binding");

  if((listen(sockfd,5))==0) //listen for connections on a socket
   printf("[+]Server is listening...\n");
  else
   perror("[-]Listening problem occured");

  size = sizeof(struct sockaddr_in);
  if((connfd=accept(sockfd,(struct sockaddr *)&cliaddr,&size))>0)
   printf("[+]Server accepted client\n");
  else
   perror("couldn't accept client");

  read(connfd, &operator,10);
  read(connfd,&operand1,sizeof(operand1));
  read(connfd,&operand2,sizeof(operand2));
  switch(operator) 
   {
        case '+': 
                result = operand1 + operand2;
                printf("Result : %d + %d = %.2f\n",operand1, operand2, result);
                break;
        case '-':
                result = operand1 - operand2;
                printf("Result : %d - %d = %.2f\n",operand1, operand2, result);
                break;
        case '*':
                result = operand1 * operand2;
                printf("Result : %d * %d = %.2f\n",operand1,operand2,result);
                break;
        case '/':
                result = (float)operand1 / operand2;
                printf("Result : %d / %d = %.2f\n",operand1,operand2,result);
                break;
        default: 
                printf("Enter operator and operands correctly");
    }
  
  write(connfd,&result,sizeof(result));   
  close(sockfd);
  return 0;
}
