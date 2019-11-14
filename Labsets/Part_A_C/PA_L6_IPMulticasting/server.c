#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <sys/socket.h>
#include <arpa/inet.h>

int main ()
{
    int sockfd;
    char msg[1024];
    struct sockaddr_in groupaddr = {AF_INET, htons(5000),inet_addr("226.1.1.1")};
    struct in_addr localInterface = {INADDR_ANY};

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    setsockopt(sockfd, IPPROTO_IP, IP_MULTICAST_IF, (char *)&localInterface, sizeof(localInterface));

    printf("Enter message : ");
    gets(msg);
    sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr*)&groupaddr, sizeof(groupaddr));
            
    return 0;
}
