#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<netdb.h>
#include<string.h>
#include<stdlib.h>

#define port 8080

void data_transfer(int conn_fd) 
{ 
	char buff[50]; 
	int n; 
	for (;;) { 
		bzero(buff, 50);  
        n = 0; 
        printf("To server : "); 
		while ((buff[n++] = getchar()) != '\n'); 
		write(conn_fd, buff, sizeof(buff)); 
        bzero(buff, 50); 
		read(conn_fd, buff, sizeof(buff)); 
        printf("From server: %s", buff); 
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Client Exit...\n"); 
			break; 
		} 
	} 
} 

int main()
{
    int socket_fd, conn_fd;
    struct sockaddr_in serveraddr;

    socket_fd=socket(AF_INET, SOCK_STREAM, 0);
    if(socket_fd == -1)
    {
        printf("Socket creation failed\n");
        exit(0);
    } 
    else
    {
        printf("Socket creation successfull\n");
    }
    
    bzero(&serveraddr,sizeof(serveraddr));

    serveraddr.sin_family=AF_INET;
    serveraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
    serveraddr.sin_port=htons(port);
    
    conn_fd=connect(socket_fd, (struct  sockaddr *)&serveraddr, sizeof(serveraddr));
    if(conn_fd != 0)
    {
        printf("Connection establishment failed\n");
        exit(0);
    } 
    else
    {
        printf("Connection establishment successfull\n");
    }

    data_transfer(socket_fd);
    close(socket_fd);

}