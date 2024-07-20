#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void* producer(void* param) {
    int item;
    while (1) {
        item = rand() % 100;  // Produce a random item
        sem_wait(&empty);
        sem_wait(&mutex);
        
        // Add item to the buffer
        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        printf("Produced: %d\n", item);
        
        sem_post(&mutex);
        sem_post(&full);
        sleep(1);  // Simulate time taken to produce an item
    }
}

void* consumer(void* param) {
    int item;
    while (1) {
        sem_wait(&full);
        sem_wait(&mutex);
        
        // Remove item from the buffer
        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        printf("Consumed: %d\n", item);
        
        sem_post(&mutex);
        sem_post(&empty);
        sleep(1);  // Simulate time taken to consume an item
    }
}

int main() {
    pthread_t tid1, tid2;

    // Initialize semaphores
    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    // Create producer and consumer threads
    pthread_create(&tid1, NULL, producer, NULL);
    pthread_create(&tid2, NULL, consumer, NULL);

    // Join the threads (this will not happen in this simple example as the loops are infinite)
    pthread_join(tid1, NULL);
    pthread_join(tid2, NULL);

    // Destroy semaphores
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}
