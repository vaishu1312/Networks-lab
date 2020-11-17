//final
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

int main()
{
struct sockaddr_in server,client;
char buff[1024];
int newfd1,i;

int sfd=socket(AF_INET,SOCK_STREAM,0);
if(sfd<0)
{   
  perror("Cannot create socket");
  exit(1);
}

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

int ls=listen(sfd,2);
if(ls<0)
{
 perror("listen error");
 exit(1);
}

int clientlen=sizeof(client);

while(1)
{
newfd1=accept(sfd,(struct sockaddr*)&client,&clientlen);
if(newfd1<0)
{
 perror("accept error");
 exit(1);
}
for(i=0;i<2;i++)
{
read(newfd1,buff,sizeof(buff));
printf("\nMessage from client  : %s\n",buff);
printf("\nEnter message to client: ");
gets(buff);
write(newfd1,buff,sizeof(buff));
}
}
close(newfd1);
close(sfd);
return 0;
}
