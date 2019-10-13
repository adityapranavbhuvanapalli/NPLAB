//Author : Aditya Pranav Bhuvanapalli
#include <netdb.h> 
#include <netinet/in.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <sys/types.h> 
#include <stdio.h>
#define SA struct sockaddr 

void serverFn(int sockfd)
{
	char buff[100];
	FILE *fp;
	bzero(buff, 100); //Clear the buffer
	read(sockfd, buff, sizeof(buff)); //Read from client
	printf("File name from client : %s\n",buff);
	fp=fopen(buff,"r");
	bzero(buff, 100);	
	while(fgets(buff,100,fp)!=-1)
	{
		write(sockfd, buff, sizeof(buff)); //Write to client
		bzero(buff, 100);
	}
	fclose(fp);
}
 
int main() 
{ 
	int sockfd, connfd, len; 
	struct sockaddr_in server, client; 

	// Creation of socket
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// Clear the socket variable
	bzero(&server, sizeof(server)); 

	// Assign IP and port of Server Socket 
	server.sin_family = AF_INET; 
	server.sin_addr.s_addr = INADDR_ANY; 
	server.sin_port = htons(8080); 

	// Bind socket to port
	bind(sockfd, (SA*)&server, sizeof(server));

	// Wait for Client 
	listen(sockfd, 5);
	len = sizeof(client); 
	connfd = accept(sockfd, (SA*)&client, &len);

	// Communicate with client 
	serverFn(connfd); 

	// Close the socket 
	close(sockfd); 
} 

