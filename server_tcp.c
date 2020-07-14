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
		read(conn_fd, buff, sizeof(buff)); 
		printf("From client: %sTo client : ", buff); 
		bzero(buff, 50); 
		n = 0; 
		while ((buff[n++] = getchar()) != '\n'); 
		write(conn_fd, buff, sizeof(buff)); 
		if (strncmp("exit", buff, 4) == 0) { 
			printf("Server Exit...\n"); 
			break; 
		} 
	} 
} 

int main()
{
    int socket_fd, conn_fd;
    struct sockaddr_in serveraddr, clientaddr;

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
    serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
    serveraddr.sin_port=htons(port);
    
    if(bind(socket_fd,(struct sockaddr *)&serveraddr, sizeof(serveraddr)) != 0)
    {
        printf("Socket binding failed\n");
        exit(0);
    }
    else
    {
        printf("Socket binded successfully\n"); 
    }
    
    if(listen(socket_fd,5) != 0)
    {
        printf("Listening failed\n");
        exit(0);
    }
    else
    {
        printf("Listening successfully\n");
    }
    
    int len=sizeof(clientaddr);
    conn_fd=accept(socket_fd, (struct  sockaddr *)&clientaddr, &len);
    if(conn_fd == -1)
    {
        printf("Connection establishment failed\n");
        exit(0);
    } 
    else
    {
        printf("Connection establishment successfull\n");
    }

    data_transfer(conn_fd);
    close(socket_fd);

}