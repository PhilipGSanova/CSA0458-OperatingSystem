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

    int *request_queue = (int*)malloc(n * sizeof(int)); // Dynamically allocate memory for request queue

    // Read the disk request queue
    printf("Enter the disk request queue:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &request_queue[i]);
    }

    // Read the initial position of the disk head
    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    // FCFS Scheduling
    printf("\nFCFS Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);

    for (int i = 0; i < n; i++) {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];
        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float) seek_time / n);

    free(request_queue); // Free the dynamically allocated memory for request queue

    return 0;
}
