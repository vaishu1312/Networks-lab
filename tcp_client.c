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
server.sin_addr.s_addr=inet_addr(argv[1]);

int cn=connect(sfd,(struct sockaddr*)&server,sizeof(server));
if(cn<0)
{
 perror("Connect error");
 exit(1);
}
//printf("\ncn: %d",cn);

printf("Enter the message: ");
scanf("%s",buff);
int n=write(sfd,buff,sizeof(buff));
close(sfd);
return 0;
}

