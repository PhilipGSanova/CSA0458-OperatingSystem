#include<stdio.h>

int main() {
    int at[10], bt[10], pr[10];  // Arrival time, Burst time, Process id
    int n, i, j, temp, time = 0, count, over = 0, sum_wait = 0, sum_turnaround = 0, start;
    float avgwait, avgturn;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input arrival time and burst time for each process
    for (i = 0; i < n; i++) {
        printf("Enter the arrival time and execution time for process %d: ", i + 1);
        scanf("%d%d", &at[i], &bt[i]);
        pr[i] = i + 1;  // Assigning process IDs
    }

    // Sorting processes by arrival time
    for (i = 0; i < n - 1; i++) {
        for (j = i + 1; j < n; j++) {
            if (at[i] > at[j]) {
                temp = at[i];
                at[i] = at[j];
                at[j] = temp;
                
                temp = bt[i];
                bt[i] = bt[j];
                bt[j] = temp;
                
                temp = pr[i];
                pr[i] = pr[j];
                pr[j] = temp;
            }
        }
    }

    // Print the process table header
    printf("\n\nProcess\t| Arrival time\t| Execution time\t| Start time\t| End time\t| Waiting time\t| Turnaround time\n\n");

    // Start processing the processes in order
    while (over < n) {
        count = 0;

        // Count how many processes have arrived by the current time
        for (i = over; i < n; i++) {
            if (at[i] <= time)
                count++;
            else
                break;
        }

        // If multiple processes have arrived at the same time, choose the shortest burst time (SJF)
        if (count > 1) {
            for (i = over; i < over + count - 1; i++) {
                for (j = i + 1; j < over + count; j++) {
                    if (bt[i] > bt[j]) {
                        temp = at[i];
                        at[i] = at[j];
                        at[j] = temp;
                        
                        temp = bt[i];
                        bt[i] = bt[j];
                        bt[j] = temp;
                        
                        temp = pr[i];
                        pr[i] = pr[j];
                        pr[j] = temp;
                    }
                }
            }
        }

        // Process the current task
        start = time;
        time += bt[over];
        printf("P[%d]\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\t|\t%d\n", pr[over], at[over], bt[over], start, time, time - at[over] - bt[over], time - at[over]);

        // Update the sum of waiting and turnaround times
        sum_wait += time - at[over] - bt[over];
        sum_turnaround += time - at[over];

        // Move to the next process
        over++;
    }

    // Calculate the average waiting time and turnaround time
    avgwait = (float)sum_wait / (float)n;
    avgturn = (float)sum_turnaround / (float)n;

    // Print the average waiting and turnaround time
    printf("\nAverage waiting time is: %.2f\n", avgwait);
    printf("Average turnaround time is: %.2f\n", avgturn);

    return 0;
}
