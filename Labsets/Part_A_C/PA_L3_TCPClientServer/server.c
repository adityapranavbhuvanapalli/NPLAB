//Author : Aditya Pranav Bhuvanapalli
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h>
#include <stdio.h>
#define SA struct sockaddr 

void serverFn(int sockfd)
{
	char buff[100]={'\0'};
	FILE *fp;
	recv(sockfd, buff, sizeof(buff),0); //Read from client
	printf("File name from client : %s\n",buff);
	fp=fopen(buff,"r");	
	while(fgets(buff,100,fp)!=-1)
	{
		send(sockfd, buff, sizeof(buff),0); //Write to client
		bzero(buff, 100);
	}
	fclose(fp);
}
 
int main() 
{  
	struct sockaddr_in server={AF_INET, htons(8080), inet_addr("127.0.0.1")}, client; 
		
	// Creation of socket
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);

	// Bind socket to server
	bind(sockfd, (SA*)&server, sizeof(server));

	// Wait for Client 
	listen(sockfd, 5);
	socklen_t len = sizeof(client); 
	int connfd = accept(sockfd, (SA*)&client, &len);

	// Communicate with client 
	serverFn(connfd); 

	// Close the socket 
	close(sockfd); 
} 

