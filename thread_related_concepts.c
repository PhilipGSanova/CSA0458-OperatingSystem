#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Thread function
void* func(void* arg) {
    printf("Inside the thread\n");
    pthread_exit(NULL); // Terminate the thread
}

// Function to create and manage threads
void fun() {
    pthread_t ptid;
    
    // Create a new thread
    if (pthread_create(&ptid, NULL, &func, NULL) != 0) {
        perror("pthread_create failed");
        exit(1);
    }

    // Check if the created thread is equal to the calling thread (main thread)
    if (pthread_equal(ptid, pthread_self())) {
        printf("Threads are equal\n");
    } else {
        printf("Threads are not equal\n");
    }

    // Detach the thread so it doesn't need to be joined
    pthread_detach(ptid);

    // The main thread will continue execution after creating the new thread
    printf("This line may be printed before thread terminates\n");

    // No need for pthread_join because the thread is detached

    // Wait for the threads to finish before exiting
    // (The main thread will exit, but it won't wait for the detached thread)

    pthread_exit(NULL); // Exit the main thread
}

int main() {
    fun();
    return 0;
}
