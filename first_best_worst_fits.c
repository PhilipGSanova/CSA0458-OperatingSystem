#include <stdio.h>

void bestfit(int mp[], int p[], int m, int n) {
    int j = 0; // Index for processes
    for (int i = 0; i < n; i++) {
        if (mp[i] >= p[j]) { // Check if partition is greater than or equal to process size
            printf("\nProcess %d fits in partition %d", p[j], mp[i]);
            mp[i] -= p[j];  // Reduce the partition size
            j++;  // Move to the next process
            if (j == m) break; // All processes are allocated
        }
    }
    for (int i = j; i < m; i++) {
        printf("\nProcess %d must wait for a partition", p[i]);
    }
}

void sort(int a[], int n) {
    // Sorting array in ascending order for Best Fit and First Fit
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] > a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void rsort(int a[], int n) {
    // Sorting array in descending order for Worst Fit
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (a[i] < a[j]) {
                int t = a[i];
                a[i] = a[j];
                a[j] = t;
            }
        }
    }
}

void firstfit(int mp[], int p[], int m, int n) {
    sort(mp, n); // Sort memory partitions in ascending order
    sort(p, m);  // Sort processes in ascending order
    bestfit(mp, p, m, n);  // Call bestfit for FirstFit logic
}

void worstfit(int mp[], int p[], int m, int n) {
    rsort(mp, n); // Sort memory partitions in descending order
    sort(p, m);   // Sort processes in ascending order
    bestfit(mp, p, m, n);  // Call bestfit for WorstFit logic
}

int main() {
    int m, n, mp[20], p[20], ch;
    
    // Input the number of memory partitions and processes
    printf("Number of memory partitions: ");
    scanf("%d", &n);
    printf("Number of processes: ");
    scanf("%d", &m);
    
    // Input the memory partitions
    printf("Enter the memory partitions:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &mp[i]);
    }
    
    // Input the process sizes
    printf("Enter process sizes:\n");
    for (int i = 0; i < m; i++) {
        scanf("%d", &p[i]);
    }
    
    // Menu to choose the allocation strategy
    printf("1. FirstFit\t2. BestFit\t3. WorstFit\nEnter your choice: ");
    scanf("%d", &ch);
    
    // Switch case to handle different strategies
    switch (ch) {
        case 1:
            firstfit(mp, p, m, n);
            break;
        case 2:
            bestfit(mp, p, m, n);
            break;
        case 3:
            worstfit(mp, p, m, n);
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
    
    return 0;
}
