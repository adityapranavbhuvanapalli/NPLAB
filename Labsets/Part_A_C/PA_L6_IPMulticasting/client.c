#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	int sockfd;
	char msg[1024];
	struct sockaddr_in addr = {AF_INET,htons(5000),inet_addr("226.1.1.1")};
	struct ip_mreq group = {inet_addr("226.1.1.1"),INADDR_ANY};

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);

	int reuse=1;
	setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)); 

	bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

	//setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group));
	setsockopt(sockfd, 0, 35, (char *)&group, sizeof(group)); 

	read(sockfd, msg, sizeof(msg));
	printf("Server : %s\n", msg);

	close(sockfd);
	return 0;
}
