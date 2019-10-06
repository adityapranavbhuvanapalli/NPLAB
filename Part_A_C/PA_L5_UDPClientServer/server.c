//Author : Aditya Pranav Bhuvanapalli 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

int main() 
{ 
	int sockfd, len, n;  
	char buff[100]; 
	struct sockaddr_in server, client; 
	
	// Creation of socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	// Clear content of server and client 
	bzero(&server, sizeof(server));
	bzero(&client, sizeof(client));
	
	// Server info 
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY; 
	server.sin_port = htons(8080); 
	
	// Bind server to the socket
	bind(sockfd, (const struct sockaddr *)&server, sizeof(server));

	// UDP Receive
	n = recvfrom(sockfd, buff, 100, MSG_WAITALL, ( struct sockaddr *) &client, &len); 
	buff[n] = '\0'; 
	printf("Client : %s\n", buff); 
	
	strcpy(buff,"Hello from the other side. Response from server.");
	// UDP Send
	sendto(sockfd, buff, strlen(buff), MSG_CONFIRM, (const struct sockaddr *) &client, len); 

	printf("Message sent to client.\n"); 
	return 0; 
} 

