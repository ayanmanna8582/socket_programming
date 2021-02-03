#include<stdio.h> 
#include<stdlib.h> 
#include<string.h> 
#include<sys/socket.h> 
#include<unistd.h>
#include<arpa/inet.h>
#include<netdb.h> 
#include<sys/socket.h> 
#define MAX 1024
#define PORT 8080 

int main() 
{ 
	int i,sockfd, connfd; 
	struct sockaddr_in servaddr, cli; 
    char buffer[MAX]; 
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (sockfd == -1) { 
		printf("[-]socket creation failed.\n"); 
		exit(0); 
	} 
	else
		printf("[+]Socket successfully created.\n"); 
	bzero(&servaddr, sizeof(servaddr)); 
 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	servaddr.sin_port = htons(PORT); 

	if (connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0) { 
		printf("[-] failed to connect with the server.\n"); 
		exit(0); 
	} 
	else
		printf("[+]connected to the server properly.\n"); 

    while(1){ 
		bzero(buffer, sizeof(buffer)); 
		printf("Enter a message for server : "); 
        i=0;
		while ((buffer[i++] = getchar()) != '\n') 
			; 
		write(sockfd, buffer, sizeof(buffer)); 
		bzero(buffer, sizeof(buffer)); 
		read(sockfd, buffer, sizeof(buffer)); 
		printf(" From Server : %s", buffer); 
		if ((strncmp(buffer, "bye", 3)) == 0) { 
			printf("[+]Client Exited...\n"); 
			break; 
		} 
	} 
	close(sockfd); 
} 

