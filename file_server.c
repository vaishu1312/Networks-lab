//final
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/stat.h>
#include <fcntl.h>  

int main()
{
struct sockaddr_in server,client;
char fname[300];
char buff[1024];
char str[100]="\0",ch[2]="\0";
int newfd1,i,j;
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
newfd1=accept(sfd,(struct sockaddr*)&client,&clientlen);

if(newfd1<0)
{
 perror("accept error");
 exit(0);
}
printf("\nWaiting for client...");
read(newfd1,fname,sizeof(fname));
printf("\nFile to be transferred is : %s\n",fname);
int fd=open(fname,O_RDONLY);

if(fd==-1)  printf("\nNo such file exists\n");

int n=read(fd,ch,1);
while(n!=0)
{
 strcat(str,ch);
 n=read(fd,ch,1); 
}
write(newfd1,str,sizeof(str));
printf("\nFile transferred\n");
close(newfd1);
close(sfd);
close(fd);
return 0;
}
