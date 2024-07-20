#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t mutex;
sem_t forks[N];

void* philosopher(void* num);
void take_forks(int);
void put_forks(int);
void test(int);

int state[N];
int phil_num[N] = {0, 1, 2, 3, 4};

#define THINKING 0
#define HUNGRY 1
#define EATING 2

void* philosopher(void* num) {
    while (1) {
        int* i = num;
        sleep(1);
        take_forks(*i);
        sleep(0);
        put_forks(*i);
    }
}

void take_forks(int phil) {
    sem_wait(&mutex);
    state[phil] = HUNGRY;
    printf("Philosopher %d is Hungry\n", phil + 1);
    test(phil);
    sem_post(&mutex);
    sem_wait(&forks[phil]);
    sleep(1);
}

void put_forks(int phil) {
    sem_wait(&mutex);
    state[phil] = THINKING;
    printf("Philosopher %d is putting fork %d and %d down\n", phil + 1, phil + 1, (phil + 1) % N + 1);
    printf("Philosopher %d is thinking\n", phil + 1);
    test((phil + 4) % N);
    test((phil + 1) % N);
    sem_post(&mutex);
}

void test(int phil) {
    if (state[phil] == HUNGRY && state[(phil + 4) % N] != EATING && state[(phil + 1) % N] != EATING) {
        state[phil] = EATING;
        printf("Philosopher %d takes fork %d and %d\n", phil + 1, phil + 1, (phil + 1) % N + 1);
        printf("Philosopher %d is Eating\n", phil + 1);
        sem_post(&forks[phil]);
    }
}

int main() {
    int i;
    pthread_t thread_id[N];
    sem_init(&mutex, 0, 1);

    for (i = 0; i < N; i++)
        sem_init(&forks[i], 0, 0);

    for (i = 0; i < N; i++) {
        pthread_create(&thread_id[i], NULL, philosopher, &phil_num[i]);
        printf("Philosopher %d is thinking\n", i + 1);
    }

    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
}
