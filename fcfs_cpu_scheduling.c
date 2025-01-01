#include <stdio.h>

int main() {
    int A[100][4]; // Array to store process information (Process ID, Burst Time, Waiting Time, Turnaround Time)
    int i, j, n, total = 0, index, temp;
    float avg_wt, avg_tat;

    // Input: Number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input: Burst Time for each process
    printf("Enter Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &A[i][1]); // Burst Time
        A[i][0] = i + 1; // Process ID
    }

    // Sorting processes by Burst Time using Selection Sort
    for (i = 0; i < n; i++) {
        index = i;
        for (j = i + 1; j < n; j++) {
            if (A[j][1] < A[index][1]) {
                index = j;
            }
        }
        // Swap burst time
        temp = A[i][1];
        A[i][1] = A[index][1];
        A[index][1] = temp;

        // Swap process ID
        temp = A[i][0];
        A[i][0] = A[index][0];
        A[index][0] = temp;
    }

    // Calculate waiting time for each process
    A[0][2] = 0; // Waiting time for the first process is 0
    for (i = 1; i < n; i++) {
        A[i][2] = 0;
        for (j = 0; j < i; j++) {
            A[i][2] += A[j][1]; // Add burst time of previous processes
        }
        total += A[i][2]; // Add waiting time to total waiting time
    }

    avg_wt = (float)total / n; // Average Waiting Time
    total = 0; // Reset total for turnaround time calculation

    // Output: Process, Burst Time, Waiting Time, Turnaround Time
    printf("\nP  BT  WT  TAT\n");
    for (i = 0; i < n; i++) {
        A[i][3] = A[i][1] + A[i][2]; // Turnaround Time = Burst Time + Waiting Time
        total += A[i][3]; // Add turnaround time to total turnaround time
        printf("P%d  %d   %d   %d\n", A[i][0], A[i][1], A[i][2], A[i][3]);
    }

    avg_tat = (float)total / n; // Average Turnaround Time

    // Output: Average Waiting Time and Turnaround Time
    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f", avg_tat);

    return 0;
}
