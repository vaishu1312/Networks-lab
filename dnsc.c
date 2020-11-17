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
struct sockaddr_in server,client;
char fname[300];
char buff[1024];
char str[100]="\0";
int newfd1,i,j;
int sfd=socket(AF_INET,SOCK_DGRAM,0);
if(sfd<0)
{   
  perror("Cannot create socket");
  exit(0);
}

bzero(&server,sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(4000);
server.sin_addr.s_addr=inet_addr(argv[1]);

//int len=sizeof(server);
while(1)
{
int len=sizeof(server);
printf("\nEnter the server name: ");
gets(str);
int n=sendto(sfd,str,sizeof(str),MSG_CONFIRM,(struct sockaddr*)&server,len);
sleep(3);
n=recvfrom(sfd,str,sizeof(str),MSG_WAITALL,(struct sockaddr*)&server,&len);
str[n]='\0';
printf("\nThe IP address is: %s\n",str);
}
close(sfd);
return 0;

}
