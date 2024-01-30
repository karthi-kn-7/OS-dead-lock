#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<pthread.h>

void *myfun(void *arg){
	int *v=(int *)arg;
	int r=*v;
	printf("value is : %d \nthe square is : %d\n",*v,r*r);
}
int main(){
	pthread_t id;
	int v=4;
	int *g;
	*g=v;
	pthread_create(&id,NULL,myfun,(void *)g);
	pthread_join(id,NULL);
	return 0;
}