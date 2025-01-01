#include <stdio.h>
#define MAX_FRAMES 3 // Maximum number of frames in memory

// Function to print the frames in memory
void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf(" - "); // Display empty frame
        } else {
            printf(" %d ", frames[i]); // Display page in frame
        }
    }
    printf("\n");
}

// Function to implement FIFO page replacement algorithm
void FIFO(int referenceString[], int n) {
    int frames[MAX_FRAMES];
    int pageFaults = 0;
    int front = 0; // Pointer for FIFO, to track the next page to be replaced

    // Initialize frames with -1 (indicating empty)
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1;
    }

    // Loop through the reference string to simulate page access
    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        int pageFound = 0;

        // Check if the page is already in the frames
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;
                break;
            }
        }

        // If the page is not found, it's a page fault
        if (!pageFound) {
            // Replace the page using FIFO logic (replace the front of the queue)
            frames[front] = page;
            front = (front + 1) % MAX_FRAMES;
            pageFaults++; // Increment page fault counter
        }

        // Print the current state of the frames
        printf("Reference String: %d | Frames: ", page);
        printFrames(frames, MAX_FRAMES);
    }

    // Print the number of page faults
    printf("\nTotal Page Faults: %d\n", pageFaults);
}

int main() {
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2}; // Reference string
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    FIFO(referenceString, n); // Call FIFO page replacement function

    return 0;
}
