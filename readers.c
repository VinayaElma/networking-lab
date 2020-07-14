#include<stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include<stdlib.h> 
#include<time.h> 
#include<unistd.h>


sem_t wrt;
sem_t mutex;
int rc = 0;
int val=1;

void *reader(void* k)
{

	while(1)
		{
		sleep(2);
		printf("Reader %d is requestinng\n",*((int *)k));
		sem_trywait(&mutex);
		rc ++;
		if (rc == 1)
			sem_trywait(&wrt);
		sem_post(&mutex);
		printf("Reader %d reads %d\n",*((int *)k),val);
		
		sem_trywait(&mutex);
		rc --;
		if (rc == 0)
			sem_post(&wrt);
		sem_post(&mutex);
	}

}


void *writer(void* k)
{
	
	while(1)
	{
		sleep(2);		
	printf("Writer %d is requestinng\n",*((int *)k));
		sem_trywait(&wrt);
		val=rand()%10+1;
		printf("Writer %d writes %d\n",*((int *)k),val);
		
		sem_post(&wrt);
	}
}



void main()
{
	int i,k;
	pthread_t read[5],write[5];
	sem_init(&mutex, 0,1);
    	sem_init(&wrt,0,1);
	srand(time(0));
    	int a[5];
    	for(i = 0; i <5; i++) 
	{
		a[i]=i;
        	pthread_create(&read[i], NULL,reader,(void *)&a[i]);
        	pthread_create(&write[i], NULL,writer,(void *)&a[i]);
    	}
    
    	for(i = 0; i < 5; i++) 
	{
        	pthread_join(read[i], NULL);
    
        	pthread_join(write[i], NULL);
    	}

    	sem_destroy(&mutex);
    	sem_destroy(&wrt);
}
