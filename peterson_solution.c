#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>
int flage[2];
int turn;
int c=0;

void init(){
	flage[0]=0;
	flage[1]=0;
	turn=0;
}
void lock(int self){
	flage[self]=1;
	turn=1-self;
	while(turn==1-self && flage[1-self]==1);
}
void unlock(int self){
	flage[self]=0;
}

void *thread0(void *a){
while(1){
	int self=*(int *)a;
	lock(self);
	printf("t0 is in CS\n");
	if(c<10)
		c++;
	printf("c: %d\n",c);
	unlock(self);
	sleep(1);
	}
}
void *thread1(void *a){
	while(1){
	int self=*(int *)a;
	lock(self);
	printf("t1 is in CS\n");
	if(c>0)
		c--;
	printf("c: %d\n",c);
	unlock(self);
	sleep(1);
	}
}
int main(){
	pthread_t p1,p2;
	init();
	int i=0;
	int j=1;
	pthread_create(&p1,NULL,thread0,(void*)&i);
	pthread_create(&p2,NULL,thread1,(void*)&j);
	pthread_join(p1,NULL);
	pthread_join(p2,NULL);
	return 0;
}