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
	
	agent = open("agentFile", O_WRONLY);
	admin = open("adminFile", O_RDONLY);

	while(1)
	{
		bzero(buff,sizeof(buff));
		read(admin,buff,100);
		printf("Agent : %s\n",buff);
		printf("\t\t\tYou : ");
		gets(buff);
		write(agent,buff,strlen(buff));
	}
	return 0; 
} 
