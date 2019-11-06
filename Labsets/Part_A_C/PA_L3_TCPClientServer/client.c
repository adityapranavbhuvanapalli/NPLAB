//Author : Aditya Pranav Bhuvanapalli 
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define SA struct sockaddr 

void clientFn(int sockfd)
{
	char buff[100]={'\0'};
	printf("Enter file name : ");	
	scanf("%s",buff);
	send(sockfd, buff, 100,0); //Send file name to server
	do
	{
		recv(sockfd, buff, 100,0); //Read file content from server
		puts(buff);
	}
	while(strcmp(buff,""));
}

int main() 
{ 
	int sockfd; 
	struct sockaddr_in server={AF_INET, htons(8080), inet_addr("127.0.0.1")}; 

	// Creation of socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);  

	// Connect to server
	connect(sockfd, (SA*)&server, sizeof(server));

	// Communicate with server
	clientFn(sockfd); 

	// Close the socket 
	close(sockfd); 
} 

