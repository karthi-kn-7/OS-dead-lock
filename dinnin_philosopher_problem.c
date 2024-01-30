#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>
sem_t ch[5];
sem_t mutex;

void eat(int i){
	printf("philosopher %d is eating\n",i);
}
//i==4 ie last philo. making last philo. to pick right and then left, and for others first left and then right 
//it is one of the way to avoid DL in Dinning philo. prob.
void *phil(void *arg){
	int i=*(int*)arg;
	if(i==4){
		sem_wait(&mutex);
		printf("philosopher%d is hungry...\n",i);
		sem_wait(&ch[(i+1)%5]);
		printf("philosopher%d picked right...\n",i);
		sem_wait(&ch[i]);
		printf("philosopher%d picked left...\n",i);
		eat(i);
		sleep(1);
		printf("philosopher%d finished eating...\n",i);
		sem_post(&ch[(i+1)%5]);
		sem_post(&ch[i]);
		sem_post(&mutex);	
	}
	else{
		sem_wait(&mutex);
		printf("philosopher%d is hungry...\n",i);
		sem_wait(&ch[i]);
		printf("philosopher%d picked left...\n",i);
		sem_wait(&ch[(i+1)%5]);
		printf("philosopher%d picked right...\n",i);
		eat(i);
		sleep(1);
		printf("philosopher%d finished eating...\n",i);
		sem_post(&ch[i]);
		sem_post(&ch[(i+1)%5]);
		sem_post(&mutex);
	}
}

int main(){
	sem_init(&mutex,0,1);
	for(int i=0;i<5;i++)
		sem_init(&ch[i],0,1);
	pthread_t p[5];
	int a[]={0,1,2,3,4};
	for(int i=0;i<5;i++){
		pthread_create(&p[i],NULL,(void *)phil,(void *)&a[i]);
		printf("phi%d is thinking\n",i);
	}
	for(int i=0;i<5;i++)
		pthread_join(p[i],NULL);
	return 0;
}