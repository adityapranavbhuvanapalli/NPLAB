//Author : Aditya Pranav Bhuvanapalli 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

int main() 
{ 
	int sockfd, n, len;; 
	char buff[100]="Hello from the other side. Request from client"; 
	struct sockaddr_in server; 

	// Creation of socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 

	// Clear the content of server
	bzero(&server, sizeof(server));
	
	// Server Info
	server.sin_family = AF_INET; 
	server.sin_addr.s_addr = INADDR_ANY;  
	server.sin_port = htons(8080); 
	
	//UDP Send
	sendto(sockfd, buff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &server, sizeof(server)); 
	printf("Message sent to server\n"); 
	
	//UDP Receive
	n = recvfrom(sockfd, buff, 100, MSG_WAITALL, (struct sockaddr *) &server, &len); 
	buff[n] = '\0'; 
	printf("Server : %s\n", buff); 

	close(sockfd); 
	return 0; 
} 

