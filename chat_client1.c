//final
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main(int argc,char **argv)
{

struct sockaddr_in server,client;
char buff[1024];
int i;
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

for(i=0;i<2;i++)
{
printf("\nEnter the message to the server: ");
gets(buff);
write(sfd,buff,sizeof(buff));
sleep(5);
read(sfd,buff,sizeof(buff));
printf("\nMessage from server: %s\n",buff);
}
close(sfd);
return 0;
}

