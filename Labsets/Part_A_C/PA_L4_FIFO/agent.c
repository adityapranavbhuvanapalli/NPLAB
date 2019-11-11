#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	int admin, agent; 
	char buff[100];

	mkfifo("agentFile", 0666); //file that agent reads and admin writes
	mkfifo("adminFile", 0666); //file that admin reads and agent writes	
	
	agent = open("agentFile", O_RDONLY);
	admin = open("adminFile", O_WRONLY);
 
	while(1)
	{
		printf("\t\t\tYou : ");
		gets(buff);
		write(admin,buff,strlen(buff));
		bzero(buff,sizeof(buff));
		read(agent,buff,100);
		printf("Admin : %s\n",buff);
	}
	return 0; 
} 
