#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>

sem_t sem;
int count = 0, pp = 0;
void producer(void){
	sem_wait(&sem);
	if(count < 5) count++;
	printf("output is %d\n", count);
	pp++;
	sem_post(&sem);
	pthread_exit(NULL);
}
void consumer(void){
	sem_wait(&sem);
	if(count > 0) count--;
	printf("output is %d\n", count);
	pp++;
	sem_post(&sem);
	pthread_exit(NULL);
}
int main(void){
	if(sem_init(&sem, 0, 1) ==-1){}
	int i = 0;
	pthread_t producers[10], consumers[10];
	for(i = 0; i < 10; i++){ pthread_create(&producers[i], NULL, (void*)producer, NULL); }
	for(i = 0; i < 10; i++){ pthread_create(&consumers[i], NULL, (void*)consumer, NULL); }
	for(i = 0; i < 10; i++){ pthread_join(producers[i], NULL); }
	for(i = 0; i < 10; i++){ pthread_join(consumers[i], NULL); }
	printf("\npp is %d\n", pp);
	pthread_exit(NULL);
}
