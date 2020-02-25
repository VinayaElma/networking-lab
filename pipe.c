
#include <stdio.h> 
#include <unistd.h> 
#include<string.h>
#include<stdlib.h>
void main() 
{ 
	char msg1[50],msg2[50]; 
	int p1[2],p2[2],i,l,cs=0,cw=1,cc=0; 

	if (pipe(p1) < 0) 
		exit(1);
	if (pipe(p2) < 0) 
		exit(1);
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
			
		for(i=0;i<l;i++)
		{

			
			cc++;
			if((msg2[i]==' ')||(msg2[i]=='\n')||(msg2[i]=='\t'))
				cw++;
			if(msg2[i]=='.')
				cs++;
				
		}
		
		write(p2[1],&cc,sizeof(cc));
		write(p2[1],&cw,sizeof(cw));
		write(p2[1],&cs,sizeof(cs));
		close(p2[1]);
exit(0);
	 
	
	}


	read(p2[0],&cc,sizeof(cc));
	read(p2[0],&cw,sizeof(cw));
	read(p2[0],&cs,sizeof(cs)); 
	close(p2[0]);

	printf("Number of characters : %d\n",cc);
	printf("Number of words : %d\n",cw);
	printf("Number of sentences : %d\n",cs);

} 

