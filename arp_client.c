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
char fname[300];
char buff[1024],ip_add[100],mac_add[100],s_mac[100]="\0",s_ip[100]="\0";
char str[100]="\0",new_str[100]="\0";
int newfd1,i,j,n;

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
 
printf("\nEnter the IP address: ");
gets(ip_add);
printf("\nEnter the MAC address: ");
gets(mac_add);

read(sfd,str,sizeof(str));
    
printf("\nARP Request Received: \n%s",str);

char* token=strtok(str,"|");
token=strtok(NULL,"|");
strcpy(s_mac,token);
token=strtok(NULL,"|");
strcpy(s_ip,token);
token=strtok(NULL,"|");
token=strtok(NULL,"|");

if(strcmp(token,ip_add)==0) 
{ 
	strcpy(new_str,"2|");
	strcat(new_str,mac_add);
	strcat(new_str,"|");
	strcat(new_str,ip_add);
	strcat(new_str,"|");
	strcat(new_str,s_ip);
	strcat(new_str,"|");
	strcat(new_str,s_mac);
	printf("\n\nIP address matches\n\nARP Reply Sent: \n%s\n",new_str); //exit(1);
	write(sfd,new_str,sizeof(new_str));
	read(sfd,new_str,sizeof(new_str));
	printf("\nReceived data Packet from : %s\n",s_mac);
	printf ("\nData received: %s\n",new_str);
}
else
{
  strcpy(str,"n");
  printf("\nThe IP address does not match\n");
  write(sfd,str,sizeof(str));
  //exit(1);
}
close(sfd);
return 0;
}
