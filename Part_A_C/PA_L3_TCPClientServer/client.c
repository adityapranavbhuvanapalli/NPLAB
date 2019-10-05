//Author : Aditya Pranav Bhuvanapalli 
#include <netdb.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#define PORT 8080 
#define SA struct sockaddr 

void clientFn(int sockfd)
{
	char buff[100];
	bzero(buff, 100); //Clear the buffer
	printf("Enter file name : ");	
	scanf("%s",buff);
	write(sockfd, buff, 100); //Send file name to server
	do
	{
		bzero(buff, 100);
		read(sockfd, buff, 100); //Read file content from server
		puts(buff);
	}
	while(strcmp(buff,""));
}

int main() 
{ 
	int sockfd, connfd; 
	struct sockaddr_in server; 

	// Creation of socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0); 

	// Clear the socket variable
	bzero(&server, sizeof(server)); 

	// Assign IP and port to the socket 
	server.sin_family = AF_INET; 
	server.sin_addr.s_addr = inet_addr("127.0.0.1"); 
	server.sin_port = htons(PORT); 

	// Connect to server
	connect(sockfd, (SA*)&server, sizeof(server));

	// Communicate with server
	clientFn(sockfd); 

	// Close the socket 
	close(sockfd); 
} 

