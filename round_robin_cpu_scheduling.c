#include<stdio.h>

int main() {
    int i, NOP, sum = 0, count = 0, y, quant, wt = 0, tat = 0, at[10], bt[10], temp[10];
    float avg_wt, avg_tat;

    printf("Total number of processes in the system: ");
    scanf("%d", &NOP);
    y = NOP;

    // Input Arrival Time and Burst Time
    for (i = 0; i < NOP; i++) {
        printf("\nEnter the Arrival and Burst time of Process[%d]\n", i + 1);
        printf("Arrival time is: \t");
        scanf("%d", &at[i]);
        printf("Burst time is: \t");
        scanf("%d", &bt[i]);
        temp[i] = bt[i];  // Store initial burst times in temp[] for processing
    }

    // Input Time Quantum
    printf("Enter the Time Quantum for the process: \t");
    scanf("%d", &quant);

    printf("\nProcess No \tBurst Time \tTAT \tWaiting Time\n");

    // Round Robin Scheduling Simulation
    for (sum = 0, i = 0; y != 0;) {
        if (temp[i] <= quant && temp[i] > 0) {  // Process completed in this round
            sum = sum + temp[i];
            temp[i] = 0;
            count = 1;
        } else if (temp[i] > 0) {  // Process requires more time
            temp[i] = temp[i] - quant;
            sum = sum + quant;
        }

        if (temp[i] == 0 && count == 1) {  // Process is finished
            y--;
            printf("Process[%d] \t\t%d\t\t\t%d\t\t\t%d\n", i + 1, bt[i], sum - at[i], sum - at[i] - bt[i]);
            wt = wt + sum - at[i] - bt[i];  // Add waiting time
            tat = tat + sum - at[i];        // Add turnaround time
            count = 0;
        }

        if (i == NOP - 1) {
            i = 0;
        } else if (at[i + 1] <= sum) {
            i++;
        } else {
            i = 0;
        }
    }

    avg_wt = (float)wt / NOP;  // Average waiting time
    avg_tat = (float)tat / NOP;  // Average turnaround time

    printf("\nAverage Turnaround Time: \t%.2f", avg_tat);
    printf("\nAverage Waiting Time: \t%.2f\n", avg_wt);

    return 0;
}
