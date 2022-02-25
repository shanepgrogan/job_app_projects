// A5.c

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>
#include <sys/wait.h>
#include <signal.h>
#include "A5.h"

#define BUFFER_SIZE 5
#define MAX_SIZE 50

typedef int buffer_item;
buffer_item buffer[BUFFER_SIZE], item;
pthread_mutex_t lock;
sem_t empty, full;
int in, out, sleepTime, numProducers, numConsumers;
char* name;

int main(int argc, char *argv[]){

	/* Step 1 */
	printf("Enter input:\n");
	char inputString[MAX_SIZE];
	fgets(inputString, MAX_SIZE, stdin);
	
	name = strtok(inputString, " ");
	sleepTime = atoi(strtok(NULL, " "));
	numProducers = atoi(strtok(NULL, " "));
	numConsumers = atoi(strtok(NULL, " "));
	
	/* Step 2 */
       	pthread_mutex_init(&lock, NULL);
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);
	in = 0, out = 0;

	/* Step 3 */
	for(int k = 0; k < BUFFER_SIZE; k++){
		buffer[k] = sizeof(buffer_item);
		buffer[k] = -1;
	}

	/* Step 4 */	
	pthread_t prodArray[BUFFER_SIZE], conArray[BUFFER_SIZE];
	
	for(int i = 0; i < numProducers; i++){
	       	parameters *data1 = (parameters*)malloc(sizeof(parameters));
		data1->num = i;	
		pthread_create(&prodArray[i], NULL, producer, data1);
	}

	/* Step 5 */
	for(int j = 0; j < numConsumers; j++){
		parameters *data2 = (parameters*)malloc(sizeof(parameters));
		data2->num = j;
		pthread_create(&conArray[j], NULL, consumer, data2);
	}
	
	sleep(sleepTime);

	/* Step 6 */
	pthread_mutex_destroy(&lock);
	sem_destroy(&empty);
	sem_destroy(&full);
	
	return 0;
		
}

void *producer(void *param){
	
	parameters *data = param;
	int threadNum = data->num;
	
	while (true) {	

		/* sleep for a random period of time: 0-4 seconds */ 
		sleep(rand() % BUFFER_SIZE);
		
		/* generate a random number */
		item = rand();
		
		/* insert an item */
		sem_wait(&empty);
		pthread_mutex_lock(&lock);
		
		insert_item(threadNum);
		
		pthread_mutex_unlock(&lock);
		sem_post(&full);
	}

	pthread_exit(0);

}

void *consumer(void *param){	
	
	parameters *data = param;
	int threadNum = data->num;

	while (true) {
		
		/* sleep for a random period of time: 0-4 seconds */ 
		sleep(rand() % BUFFER_SIZE);
		
		/* remove an item */
		sem_wait(&full);
		pthread_mutex_lock(&lock);
		
		remove_item(threadNum);
		
		pthread_mutex_unlock(&lock);
		sem_post(&empty);
	}

	pthread_exit(0);

}

void insert_item(int num){

	int val1, val2;
	sem_getvalue(&full, &val1);
	sem_getvalue(&empty, &val2);

	buffer[in] = item;
	printf("Producer %d inserted item %d into buffer[%d]\n", num, item, in);
	in = (in+1) % BUFFER_SIZE;

}

void remove_item(int num){

	int val1, val2;
	sem_getvalue(&full, &val1);
	sem_getvalue(&empty, &val2);

	buffer_item item = buffer[out];
	buffer[out] = -1;	
	printf("Consumer %d removed item %d from buffer[%d]\n", num, item, out);
	out = (out+1) % BUFFER_SIZE;

}


