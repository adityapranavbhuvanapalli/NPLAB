#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h>
#include <arpa/inet.h>

int main()
{
	int sockfd;
	char msg[1024];
	struct sockaddr_in addr = {AF_INET,htons(5000),INADDR_ANY};
	struct ip_mreq group = {inet_addr("226.1.1.1"),INADDR_ANY};

	sockfd = socket(AF_INET, SOCK_DGRAM, 0);
	bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));

	setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group));

	read(sockfd, msg, sizeof(msg));
	printf("Server : %s\n", msg);

	close(sockfd);
	return 0;
}
