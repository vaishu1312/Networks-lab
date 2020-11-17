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

typedef struct{
char server_name[100];
char ip_addr[3][100];
}dns;

int main()
{
struct sockaddr_in server,client;
char choice[100],d_name[100],ip_add[100],ip2[100];
char str[100]="\0",new_str[100];
int newfd1,i=0;
int j,num,k,x,y;
dns table[5];

for(j=0;j<5;j++) for(k=0;k<3;k++) strcpy(table[j].ip_addr[k],"");

strcpy(table[0].server_name,"www.yahoo.com"); 
strcpy(table[0].ip_addr[0],"10.2.45.67");
strcpy(table[1].server_name,"www.google.com");
strcpy(table[1].ip_addr[0],"142.89.78.66");
strcpy(table[2].server_name,"www.annauniv.edu");
strcpy(table[2].ip_addr[0],"197.34.53.122");

int sfd=socket(AF_INET,SOCK_DGRAM,0);
if(sfd<0)
{   
  perror("Cannot create socket");
  exit(0);
}
bzero(&server,sizeof(server));
server.sin_family=AF_INET;
server.sin_port=htons(4000);
server.sin_addr.s_addr=htonl(INADDR_ANY);
int bs=bind(sfd,(struct sockaddr*)&server,sizeof(server));
if(bs<0)
{
 perror("Bind error");
 exit(1);
}

printf("\nDo you want to modify (yes or no): ");
scanf("%s",choice);
if(strcmp(choice,"yes")==0)
{
	getchar();
	printf("\nEnter Domain name: ");
	gets(d_name);
	for(j=0;j<5;j++)
		if(strcmp(table[j].server_name,d_name)==0) break;
	if(j==5)
	{  printf("Invalid domain name\n"); 
		 printf("\nEnter domain name: ");
		 gets(d_name);
	}	
	printf("Enter IP address: ");
	gets(ip_add); strcpy(ip2,ip_add);
	char* token=strtok(ip2,".");
	while(token!=NULL)
	{
		num=atoi(token);
		if(num>255)
		{
		printf("Invalid IP address"); 
		printf("\nEnter a valid IP address: ");
		gets(ip_add);
		break; 
		}
		token=strtok(NULL,".");
	}

	for(k=0;k<5;k++)
	{	
         if( (strcmp(table[k].server_name,d_name)==0) && (strcmp(table[k].ip_addr[0],ip_add)==0) )
	 {
 	  printf("IP address already exists"); 
	  printf("\nEnter valid IP address: ");
	  gets(ip_add);
 	  break;
	 }
        }
	strcpy(table[j].ip_addr[1],ip_add);	
  printf("\nSucessfully modified");
	printf("\nThe updated table is:\n");
	printf("\nServer name\t IP address");
  for(x=0;x<3;x++)
	{
   printf("\n%s\t",table[x].server_name);
	 for(y=0;y<2;y++)
		 printf("%s\n\t\t",table[x].ip_addr[y]);
	}
}//end if yes

//printf("\n%sdone",table[j].ip_addr[1]); exit(1);


while(1)
{
int len=sizeof(client);
int n=recvfrom(sfd,str,sizeof(str),MSG_WAITALL,(struct sockaddr*)&client,&len);
str[n]='\0';
//printf("\nMessage from client: %s",str);
for(j=0;j<5;j++)
{
	if(strcmp(table[j].server_name,str)==0)
		{
		 k=0; strcpy(str,""); strcpy(new_str,"");
		 	 while(strcmp(table[j].ip_addr[k],"")!=0 && k<3)
		 {  strcpy(new_str, table[j].ip_addr[k]); 
			  if(strcmp(table[j].ip_addr[k+1],"")!=0  && k<2)  
			strcat(new_str," and ");
		          strcat(str,new_str);  
			  k++;
		       }
		 i=1;
		 break;
		}
	}
	if(i==0)  strcpy(str,"No such server exists");
	n=sendto(sfd,str,sizeof(str),MSG_CONFIRM,(struct sockaddr*)&client,len);
}
close(sfd);
return 0;
}
