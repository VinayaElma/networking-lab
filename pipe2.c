
#include <stdio.h> 
#include <unistd.h> 
#include<string.h>
#include<stdlib.h>
void main() 
{ 
	char msg1[50],msg2[50],msg[50]; 
	int p1[2],p2[2],i,l,l1,j; 

	if (pipe(p1) < 0) 
		exit(1);
	if (pipe(p2) < 0) 
		exit(1);
	printf("Enter string1 :");
	gets(msg1);
	l=strlen(msg1);
	write(p1[1], msg1,l);
 	close(p1[1]);
	
	
	pid_t pid;
	pid=fork();
	if(pid==0)
	{
		
		read(p1[0], msg2, l); 
		close(p1[0]);
		printf("\nEnter string2 :");
		gets(msg);
		i=l;
		for (j = 0; msg[j] != '\0';++i,++j) 
        		msg2[i] = msg[j];
		
		msg2[i]='\0';
		l1=strlen(msg2);
		write(p2[1],msg2,l1);
		close(p2[1]);
		exit(0);
	 
	
	}


	read(p2[0],msg1,l1);
	close(p2[0]);

	printf("\nString is %s \n",msg1);

} 

