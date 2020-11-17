#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

int main()
{
struct sockaddr_in server,client;
char buff[1024];
char str[1000];

int sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{   
  perror("Cannot create socket");
  exit(1);
}
//printf("\nsfd: %d",sfd);

bzero(&server,sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(3000);
server.sin_addr.s_addr=htonl(INADDR_ANY);
int bs=bind(sfd,(struct sockaddr*)&server,sizeof(server));
if(bs<0)
{
 perror("Bind error");
 exit(1);
}
//printf("\nbs: %d",bs);

int ls=listen(sfd,2);
if(ls<0)
{
 perror("listen error");
 exit(1);
}
//printf("\nls: %d",ls);

int clientlen=sizeof(client);
int newfd=accept(sfd,(struct sockaddr*)&client,&clientlen);
if(newfd<0)
{
 perror("accept error");
 exit(1);
}
//printf("\nnewfd: %d",newfd);

int n=read(newfd,buff,sizeof(buff));
printf("\nReceived Message is: %s\n",buff);
close(sfd);
close(newfd);
return 0;
}
