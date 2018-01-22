#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t sem;
int count = 0;

void inc(void){
	sem_wait(&sem);
	int i = 0;
	for (i = 0; i < 25000000; i++)
	{
		count++;
	}
	sem_post(&sem);
	pthread_exit(NULL);
}
void dec(void){
	sem_wait(&sem);
	int i = 0;
	for (i = 0; i < 25000000; i++)
	{
		count--;
	}
	sem_post(&sem);
	pthread_exit(NULL);
}

int main(void){
	if(sem_init(&sem, 0, 1) ==-1){}
	int i = 0;
	pthread_t id[4];
	pthread_create(&id[0], NULL, (void*)dec, NULL);
	pthread_create(&id[1], NULL, (void*)inc, NULL);
	pthread_create(&id[2], NULL, (void*)dec, NULL);
	pthread_create(&id[3], NULL, (void*)inc, NULL);
	for(i = 0; i < 4; i++){
		pthread_join(id[i], NULL);
	}
	printf("\noutput is %d\n", count);
	pthread_exit(NULL);
}
