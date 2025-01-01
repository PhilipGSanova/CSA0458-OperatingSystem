#include <stdio.h>
#include <stdlib.h>
#define MAX_FRAMES 3

// Function to print the current state of frames
void printFrames(int frames[], int n) {
    for (int i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf(" - "); // Empty frame
        } else {
            printf(" %d ", frames[i]); // Page in frame
        }
    }
    printf("\n");
}

int main() {
    int frames[MAX_FRAMES];
    int usageHistory[MAX_FRAMES]; // To store the usage history of pages

    // Initialize frames and usage history
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
        usageHistory[i] = 0; // Initialize usage history
    }

    int pageFaults = 0;
    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    // Print the reference string
    printf("Reference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", referenceString[i]);
    }
    printf("\n\n");

    printf("Page Replacement Order:\n");

    // Process each page in the reference string
    for (int i = 0; i < n; i++) {
        int page = referenceString[i];
        int pageFound = 0;

        // Check if the page is already in memory (page hit)
        for (int j = 0; j < MAX_FRAMES; j++) {
            if (frames[j] == page) {
                pageFound = 1;

                // Update the usage history by incrementing the counters for other pages
                for (int k = 0; k < MAX_FRAMES; k++) {
                    if (k != j) {
                        usageHistory[k]++;
                    }
                }

                // Reset the usage counter for the used page
                usageHistory[j] = 0;
                break;
            }
        }

        // If the page is not found, it's a page fault
        if (!pageFound) {
            printf("Page %d -> ", page);

            // Find the page with the maximum usage counter (least recently used)
            int lruPage = 0;
            for (int j = 1; j < MAX_FRAMES; j++) {
                if (usageHistory[j] > usageHistory[lruPage]) {
                    lruPage = j;
                }
            }

            // Replace the least recently used page
            int replacedPage = frames[lruPage];
            frames[lruPage] = page;
            usageHistory[lruPage] = 0;

            // Print the replacement info
            if (replacedPage != -1) {
                printf("Replace %d with %d: ", replacedPage, page);
            } else {
                printf("Load into an empty frame: ");
            }

            // Print the current state of frames
            printFrames(frames, MAX_FRAMES);

            // Increment page faults
            pageFaults++;
        }
    }

    // Print total page faults
    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}
