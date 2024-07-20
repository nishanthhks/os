#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>

#define N 5  // Number of philosophers and forks
#define THINKING 2
#define HUNGRY 1
#define EATING 0
#define LEFT (phnum + 4) % N  // Index of left neighbor
#define RIGHT (phnum + 1) % N // Index of right neighbor

int state[N]; // Array to keep track of each philosopher's state
int phil[N] = { 0, 1, 2, 3, 4 }; // Philosophers' index numbers

sem_t mutex; // Semaphore for mutual exclusion
sem_t S[N];  // Semaphores for each philosopher

// Function to check if a philosopher can start eating
void test(int phnum) {
    if (state[phnum] == HUNGRY && state[LEFT] != EATING && state[RIGHT] != EATING) {
        state[phnum] = EATING;
        sleep(2); // Simulate eating time
        printf("Philosopher %d takes chopstick %d and %d\n", phnum + 1, LEFT + 1, phnum + 1);
        printf("Philosopher %d is Eating\n", phnum + 1);
        sem_post(&S[phnum]); // Signal that the philosopher can eat
    }
}

// Function for a philosopher to take forks
void take_fork(int phnum) {
    sem_wait(&mutex); // Enter critical region
    state[phnum] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phnum + 1);
    test(phnum); // Try to acquire forks
    sem_post(&mutex); // Exit critical region
    sem_wait(&S[phnum]); // Wait if forks are not available
    sleep(1); // Simulate the time taken to take the forks
}

// Function for a philosopher to put down forks
void put_fork(int phnum) {
    sem_wait(&mutex); // Enter critical region
    state[phnum] = THINKING;
    printf("Philosopher %d putting fork %d and %d down\n", phnum + 1, LEFT + 1, phnum + 1);
    printf("Philosopher %d is thinking\n", phnum + 1);
    test(LEFT);  // See if the left neighbor can now eat
    test(RIGHT); // See if the right neighbor can now eat
    sem_post(&mutex); // Exit critical region
}

// Function representing the behavior of a philosopher
void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1);    // Philosopher is thinking
        take_fork(*i); // Try to take forks to eat
        sleep(0);    // Simulate eating
        put_fork(*i); // Put down forks and start thinking
    }
}

int main() {
    int i;
    pthread_t thread_id[N];

    sem_init(&mutex, 0, 1); // Initialize mutex semaphore
    for (i = 0; i < N; i++)
        sem_init(&S[i], 0, 0); // Initialize semaphore for each philosopher

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil[i]); // Create philosopher threads
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL); // Wait for all philosopher threads to finish
}
