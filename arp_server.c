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
char mac_add[100],ip_add[100],d_ip[100],d_mac[100]="00-00-00-00-00-00";
char data[100]="\0",r_str[100],str[100],new_str[100]="\0";
int newfd1,i=0;
int j,num,k,x,y,n;

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

printf("\nEnter the Server's IP address: ");
gets(ip_add);
printf("\nEnter the Server's MAC address: ");
gets(mac_add);
printf("\nEnter the details of packet received:");
printf("\nEnter Destination IP : ");
gets(d_ip);
printf("\nEnter the 16 bit data: ");
gets(data);
printf("\nDeveloping ARP Request packet..");

strcpy(str,"1|");
strcat(str,mac_add);
strcat(str,"|");
strcat(str,ip_add);
strcat(str,"|");
strcat(str,d_mac);
strcat(str,"|");
strcat(str,d_ip);
printf("\n\nThe ARP request packet is:\n%s ",str);   
      
int clientlen=sizeof(client);    
printf("\nThe ARP Request packet is broadcasted.\n\nWaiting for ARP Reply...\n");  

strcpy(r_str,str);
       
for(j=0;j<3;j++)
{
    
newfd1=accept(sfd,(struct sockaddr*)&client,&clientlen);
if(newfd1<0)
{
 perror("accept error");
 exit(0);
}   
		  
write(newfd1,str,sizeof(str));
//sleep(5);       
read(newfd1,r_str,sizeof(str));
        
if (strcmp(r_str,"n")!=0)
{	
 	printf("\nARP Reply received:\n%s\n",r_str);
	char* token=strtok(r_str,"|");
	token=strtok(NULL,"|");
	strcpy(d_mac,token);
	printf("\nSending data packet to: %s\n",d_mac);
        write(newfd1, data, sizeof(data));
}
}
close(newfd1);
close(sfd);
return 0;
}
