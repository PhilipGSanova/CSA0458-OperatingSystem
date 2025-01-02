#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

// Mutex for each chopstick
pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

// Philosopher lifecycle (thinking, eating, etc.)
void* philosopherLifeCycle(void* arg) {
    int id = *((int*)arg);
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Think
        printf("Philosopher %d is thinking...\n", id);
        sleep(rand() % 3 + 1); // Thinking time

        // Pick up chopsticks
        printf("Philosopher %d is picking up chopsticks...\n", id);
        pthread_mutex_lock(&chopsticks[left_chopstick]);
        pthread_mutex_lock(&chopsticks[right_chopstick]);

        // Eat
        printf("Philosopher %d is eating...\n", id);
        sleep(rand() % 3 + 1); // Eating time

        // Put down chopsticks
        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        pthread_mutex_unlock(&chopsticks[right_chopstick]);

        // Repeat the cycle
    }

    return NULL;
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int philosopher_ids[NUM_PHILOSOPHERS];

    // Initialize mutex locks for each chopstick
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosopher_ids[i] = i;
        if (pthread_create(&philosophers[i], NULL, philosopherLifeCycle, (void*)&philosopher_ids[i]) != 0) {
            perror("pthread_create");
            exit(1);
        }
    }

    // Wait for threads to finish (they run indefinitely, so this part is never reached)
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        if (pthread_join(philosophers[i], NULL) != 0) {
            perror("pthread_join");
            exit(1);
        }
    }

    // Destroy mutex locks
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}
