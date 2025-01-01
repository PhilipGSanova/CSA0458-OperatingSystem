#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

sem_t mutex, writeBlock;
int data = 0, readersCount = 0;

void *reader(void *arg) {
    int id = *((int *)arg);
    int i = 0;
    while (i < 10) {
        sem_wait(&mutex);
        readersCount++;
        if (readersCount == 1) {
            sem_wait(&writeBlock);
        }
        sem_post(&mutex);

        // Reading operation
        printf("Reader %d reads data: %d\n", id, data);

        sem_wait(&mutex);
        readersCount--;
        if (readersCount == 0) {
            sem_post(&writeBlock);
        }
        sem_post(&mutex);
        i++;
    }
    return NULL;
}

void *writer(void *arg) {
    int id = *((int *)arg);
    int i = 0;
    while (i < 10) {
        sem_wait(&writeBlock);

        // Writing operation
        data++;
        printf("Writer %d writes data: %d\n", id, data);

        sem_post(&writeBlock);
        i++;
    }
    return NULL;
}

int main() {
    pthread_t readers[5], writers[3];
    int readerIds[5] = {1, 2, 3, 4, 5};
    int writerIds[3] = {1, 2, 3};

    sem_init(&mutex, 0, 1);
    sem_init(&writeBlock, 0, 1);

    // Create reader threads
    for (int i = 0; i < 5; i++) {
        pthread_create(&readers[i], NULL, reader, &readerIds[i]);
    }

    // Create writer threads
    for (int i = 0; i < 3; i++) {
        pthread_create(&writers[i], NULL, writer, &writerIds[i]);
    }

    // Wait for reader threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(readers[i], NULL);
    }

    // Wait for writer threads to finish
    for (int i = 0; i < 3; i++) {
        pthread_join(writers[i], NULL);
    }

    sem_destroy(&mutex);
    sem_destroy(&writeBlock);

    return 0;
}
