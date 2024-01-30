#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
sem_t full;
sem_t empty;
pthread_mutex_t mutex;
int in=0,out=0,buffer[10];

void *pro(void* arg){
	//for user defined option remove while loop
	//while(1){
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		int i=rand() % 100;
		buffer[in]=i;
		in=(in+1)%10;
		printf("produced : %d\n",i);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	//}
}
void *con(void* arg){
	//while(1){
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		int data=buffer[out];
		out=(out+1)%10;
		printf("consumed : %d\n",data);
		
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	//}
}
int main(){
	sem_init(&empty,0,10);
	sem_init(&full,0,0);
	pthread_mutex_init(&mutex,NULL);
	int value,data,i;
	
	pthread_t pr,co;
	while(1){
		printf("1-pro\n2-cons\n3-exit\n");
		printf("enter your choice : ");
		scanf("%d",&i);
		if(i==1){
			sem_getvalue(&empty,&value);
			if((&mutex) && value!=0){
				pthread_create(&pr,NULL,(void *)pro,(void *)pr);
				pthread_join(pr,NULL);
			}
			else{
				printf("buffer full..\n");
			}
		}
		else if(i==2){
			sem_getvalue(&full,&value);
			if((&mutex) && value!=0){
				pthread_create(&co,NULL,(void *)con,(void *)co);
				pthread_join(co,NULL);
			}
			else{
				printf("buffer empty....\n");
			}
		}
		else{
			printf("exiting ...\n");
			break;
		}
	}
	pthread_mutex_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);
	return 0;
}