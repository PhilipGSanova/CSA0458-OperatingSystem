#include <stdio.h>
#include <stdlib.h>

int main() {
    int n, head, seek_time = 0;

    // Read the number of disk requests
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    // Handle edge case for zero requests
    if (n == 0) {
        printf("No disk requests to process.\n");
        return 0;
    }

    // Dynamically allocate memory for the request queue
    int* request_queue = (int*)malloc(n * sizeof(int));

    // Read the disk request queue
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }

    // Read the initial position of the disk head
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    // Sort the request queue to simplify C-SCAN algorithm
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (request_queue[i] > request_queue[j]) {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    // C-SCAN Scheduling
    printf("\nC-SCAN Disk Scheduling:\n");

    // The C-SCAN logic: move from head towards the rightmost request, 
    // then jump to the leftmost request and move towards the right again
    int start = 0, end = n - 1;

    // Seek to the rightmost request from the current head position
    while (request_queue[start] < head) {
        start++;  // Find the first request that is greater than or equal to head
    }

    // Move head to the rightmost request
    for (int i = start; i <= end; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf("%d ", head);
    }

    // Jump to the lowest position in the queue (wrap around)
    seek_time += abs(head - request_queue[0]);
    head = request_queue[0];
    printf("%d ", head);

    // Continue serving requests in increasing order of disk position
    for (int i = 1; i < start; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf("%d ", head);
    }

    // Display total and average seek time
    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    // Free dynamically allocated memory
    free(request_queue);

    return 0;
}
