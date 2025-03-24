#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h> // Include this for time()

#define BUFFER_SIZE 15
#define MAX_ITEM 5

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t mutex, empty, full;

void* producer(void* arg) {
    for (int i = 0; i < MAX_ITEM; i++) {
        int item = rand() % 100; 

        sem_wait(&empty);   
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Produced: %d\n", item);
        in = (in + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&full);

        sleep(1);  
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < MAX_ITEM; i++) {
        sem_wait(&full);     
        sem_wait(&mutex);

        int item = buffer[out];
        printf("Consumed: %d\n", item);
        out = (out + 1) % BUFFER_SIZE;

        sem_post(&mutex);
        sem_post(&empty);

        sleep(2);  
    }
    return NULL;
}

int main() {
	srand(time(NULL)); // Initialize random seed

	pthread_t producer_thread, consumer_thread;

	sem_init(&mutex, 0, 1);
	sem_init(&empty, 0, BUFFER_SIZE);
	sem_init(&full, 0, 0);

	pthread_create(&producer_thread, NULL, producer, NULL);
	pthread_create(&consumer_thread, NULL, consumer, NULL);

	pthread_join(producer_thread, NULL);
	pthread_join(consumer_thread, NULL);

	sem_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);

	return 0;
}

