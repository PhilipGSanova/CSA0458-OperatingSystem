#include <stdio.h>
#include <stdlib.h>

int mutex = 1;
int full = 0;
int empty = 10, x = 0;  // Buffer size is 10

// Producer function
void producer() {
    --mutex;      // Lock the mutex
    ++full;       // Increase full buffer
    --empty;      // Decrease empty buffer space
    x++;          // Produce an item
    printf("\nProducer produces item %d", x);
    ++mutex;      // Unlock the mutex
}

// Consumer function
void consumer() {
    --mutex;      // Lock the mutex
    --full;       // Decrease full buffer
    ++empty;      // Increase empty buffer space
    printf("\nConsumer consumes item %d", x);
    x--;          // Consume an item
    ++mutex;      // Unlock the mutex
}

int main() {
    int n, i;
    
    // Menu
    printf("\n1. Press 1 for Producer"
           "\n2. Press 2 for Consumer"
           "\n3. Press 3 for Exit");

    // Loop for user input
    for (i = 1; i > 0; i++) {
        printf("\nEnter your choice: ");
        scanf("%d", &n);

        switch (n) {
            case 1:
                if (mutex == 1 && empty != 0) {
                    producer();  // Call producer function
                } else {
                    printf("Buffer is full!");
                }
                break;
            case 2:
                if (mutex == 1 && full != 0) {
                    consumer();  // Call consumer function
                } else {
                    printf("Buffer is empty!");
                }
                break;
            case 3:
                exit(0);  // Exit the program
                break;
            default:
                printf("Invalid choice! Please try again.");
        }
    }

    return 0;
}
