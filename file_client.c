//final
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include <fcntl.h>  

int main(int argc,char **argv)
{

struct sockaddr_in server;
char buff[1024];
char str[1000];

int sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{   
  perror("Cannot create socket");
  exit(1);
}

bzero(&server,sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(3000);
server.sin_addr.s_addr=inet_addr(argv[1]);

int cn=connect(sfd,(struct sockaddr*)&server,sizeof(server));
if(cn<0)
{
 perror("Connect error");
 exit(1);
}
else
 printf("Connected to the server..\n"); 

printf("\nEnter the path of the file: ");
gets(buff);
write(sfd,buff,sizeof(buff));
printf("\nFile transferred");
read(sfd,buff,sizeof(buff));
printf("\nEnter the path in which the file is to be saved: ");
scanf("%s",str);
int fd=creat(str,O_RDWR);
write(fd,buff,strlen(buff));
//printf("\ncontents: %s end\n",buff);
close(sfd);
close(fd);
return 0;
}

