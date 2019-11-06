//Author : Aditya Pranav Bhuvanapalli 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 

int main() 
{ 
	int sockfd, len, n;  
	char buff[100]; 
	struct sockaddr_in server={AF_INET, htons(8080), inet_addr("127.0.0.1")}, client; 
	
	// Creation of socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// Bind server to the socket
	bind(sockfd, (const struct sockaddr *)&server, sizeof(server));

	// UDP Receive
	n = recvfrom(sockfd, buff, 100, 0, ( struct sockaddr *) &client, &len); 
	buff[n] = '\0'; 
	printf("Client : %s\n", buff); 
	
	strcpy(buff,"Hello from the other side. Response from server.");
	// UDP Send
	sendto(sockfd, buff, strlen(buff), 0, (const struct sockaddr *) &client, len); 

	printf("Message sent to client.\n"); 
	return 0; 
} 

