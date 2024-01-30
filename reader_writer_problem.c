#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<semaphore.h>

//reader writer na 2 semaphore both are 1
//sem wrt to control writing

//mutex to control if any change occur in read count initialized to 0
//int read count

sem_t wrt;
pthread_mutex_t mutex;
int value=1;
int rc=0;

void *writer(void* arg){
	sem_wait(&wrt);
	value+=10;
	printf("writer%d : %d\n",*(int *)arg,value);
	sem_post(&wrt);
}
void *reader(void *arg){
	pthread_mutex_lock(&mutex);
	rc++;
	if(rc==1)
		sem_wait(&wrt);
	pthread_mutex_unlock(&mutex);
	
	printf("reader%d : %d\n",*(int *)arg,value);
	
	pthread_mutex_lock(&mutex);
	rc--;
	if(rc==0)
		sem_post(&wrt);
	pthread_mutex_unlock(&mutex);
}


int main(){
	pthread_t wr[3],re[3];
	sem_init(&wrt,0,1);
	int a[]={1,2,3};
	for(int i=0 ;i<3;i++)
		pthread_create(&wr[i],NULL,(void *)writer,(void *)&a[i]);
	for(int i=0;i<3;i++)
		pthread_create(&re[i],NULL,(void *)reader,(void *)&a[i]);
	for(int i=0 ;i<3;i++)
		pthread_join(wr[i],NULL);
	for(int i=0 ;i<3;i++)
		pthread_join(re[i],NULL);
		
	sem_destroy(&wrt);
	pthread_mutex_destroy(&mutex);
	return 0;
}