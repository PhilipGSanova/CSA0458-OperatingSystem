#include <stdio.h>

int main() {
    int bt[20], p[20], wt[20], tat[20], i, j, n, total = 0, pos, temp;
    float avg_wt, avg_tat;

    // Input: Number of processes
    printf("Enter number of processes: ");
    scanf("%d", &n);

    // Input: Burst Time for each process
    printf("Enter Burst Time for each process:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1;  // Process ID
    }

    // Sorting processes by Burst Time using Selection Sort
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos]) {
                pos = j;
            }
        }
        // Swap burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap process ID
        temp = p[i];
        p[i] = p[pos];
        p[pos] = temp;
    }

    // Calculate waiting time for each process
    wt[0] = 0;  // Waiting time for the first process is 0
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j];  // Add burst time of previous processes
        }
        total += wt[i];  // Add waiting time to total waiting time
    }

    avg_wt = (float)total / n;  // Average Waiting Time
    total = 0;  // Reset total for turnaround time calculation

    // Output: Process, Burst Time, Waiting Time, Turnaround Time
    printf("\nProcess  Burst Time  Waiting Time  Turnaround Time\n");
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];  // Turnaround Time = Burst Time + Waiting Time
        total += tat[i];  // Add turnaround time to total turnaround time
        printf("P%d       %d           %d              %d\n", p[i], bt[i], wt[i], tat[i]);
    }

    avg_tat = (float)total / n;  // Average Turnaround Time

    // Output: Average Waiting Time and Turnaround Time
    printf("\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f", avg_tat);

    return 0;
}
