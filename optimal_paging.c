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
    for (int i = 0; i < MAX_FRAMES; i++) {
        frames[i] = -1; // Initialize frames to -1 (empty)
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
                pageFound = 1; // Page hit, no replacement
                break;
            }
        }

        // If the page is not found, it's a page fault
        if (!pageFound) {
            printf("Page %d -> ", page);
            
            // Find the page that will not be used for the longest time (optimal page to replace)
            int optimalPage = -1;
            int farthestDistance = 0;

            // Check the future usage of each page in memory
            for (int j = 0; j < MAX_FRAMES; j++) {
                int futureDistance = 0;
                
                // Find how far in the future this page will be used
                for (int k = i + 1; k < n; k++) {
                    if (referenceString[k] == frames[j]) {
                        break;
                    }
                    futureDistance++;
                }

                // Track the page with the farthest future distance (least optimal to keep)
                if (futureDistance > farthestDistance) {
                    farthestDistance = futureDistance;
                    optimalPage = j;
                }
            }

            // Replace the page that will not be used for the longest time
            frames[optimalPage] = page;
            printFrames(frames, MAX_FRAMES);
            pageFaults++;
        }
    }

    // Print total page faults
    printf("\nTotal Page Faults: %d\n", pageFaults);
    return 0;
}
