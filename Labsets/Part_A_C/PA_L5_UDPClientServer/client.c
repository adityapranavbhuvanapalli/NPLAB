//Author : Aditya Pranav Bhuvanapalli 
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 

int main() 
{ 
	int sockfd, n, len;; 
	char buff[100]="Hello from the other side. Request from client"; 
	struct sockaddr_in server={AF_INET, htons(8080), inet_addr("127.0.0.1")}; 

	// Creation of socket
	sockfd = socket(AF_INET, SOCK_DGRAM, 0); 
	
	//UDP Send
	sendto(sockfd, buff, strlen(buff), 0, (const struct sockaddr *) &server, sizeof(server)); 
	printf("Message sent to server\n"); 
	
	//UDP Receive
	n = recvfrom(sockfd, buff, 100, 0, (struct sockaddr *) &server, &len); 
	buff[n] = '\0'; 
	printf("Server : %s\n", buff); 

	close(sockfd); 
	return 0; 
} 

