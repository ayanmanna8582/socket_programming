#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<unistd.h>
#include<netdb.h> 
#include<netinet/in.h> 
#include<sys/socket.h> 
#include<sys/types.h> 
#define MAX 1024
#define PORT 8080 

int main() 
{ 
	int i,sockfd, connfd, len; 
	struct sockaddr_in servaddr, cli; 
    char buffer[MAX]; 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) 
    { 
		printf("[-]socket creation failed.\n"); 
		exit(0); 
	} 
	else
		printf("[+]Socket successfully created.\n"); 
	bzero(&servaddr, sizeof(servaddr)); 

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
	servaddr.sin_port = htons(PORT); 

	if ((bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))) != 0) { 
		printf("[-]socket failed to bind.\n"); 
		exit(0); 
	} 
	else
		printf("[+]Socket successfully binded.\n"); 

	if ((listen(sockfd, 6)) != 0) { 
		printf("[-]Listening failed.\n"); 
		exit(0); 
	} 
	else
		printf("[+]Server is listening.....\n"); 
	len = sizeof(cli); 

	connfd = accept(sockfd, (struct sockaddr*)&cli, &len); 
	if (connfd < 0) { 
		printf("[-]server failed to accept client.\n"); 
		exit(0); 
	} 
	else
		printf("[+]server acccepted the client.\n"); 

    while(1){ 
		bzero(buffer, MAX);  
		read(connfd, buffer, sizeof(buffer)); 
        printf("From client: %s To client : ", buffer); 
		bzero(buffer, MAX); 
        i=0; 
		while ((buffer[i++] = getchar()) != '\n') 
			; 
		write(connfd, buffer, sizeof(buffer)); 
		if (strncmp( buffer,"bye", 3) == 0) { 
			printf("[+]Server Exited.\n"); 
			break; 
		} 
	} 
	close(sockfd); 
} 

