#include<stdio.h>

struct priority_scheduling {
    char process_name;
    int burst_time;
    int waiting_time;
    int turn_around_time;
    int priority;
};

int main() {
    int number_of_process, total = 0, position;
    struct priority_scheduling temp_process;
    int ASCII_number = 65;  // ASCII value of 'A'
    float average_waiting_time, average_turnaround_time;

    // Input: Number of Processes
    printf("Enter the total number of Processes: ");
    scanf("%d", &number_of_process);

    struct priority_scheduling process[number_of_process];

    // Input: Burst Time and Priority for each process
    printf("\nPlease Enter the Burst Time and Priority of each process:\n");
    for (int i = 0; i < number_of_process; i++) {
        process[i].process_name = (char)ASCII_number;
        printf("\nEnter the details of the process %c \n", process[i].process_name);
        printf("Enter the burst time: ");
        scanf("%d", &process[i].burst_time);
        printf("Enter the priority: ");
        scanf("%d", &process[i].priority);
        ASCII_number++;
    }

    // Sorting processes by priority (Highest priority first)
    for (int i = 0; i < number_of_process; i++) {
        position = i;
        for (int j = i + 1; j < number_of_process; j++) {
            if (process[j].priority > process[position].priority) {
                position = j;
            }
        }
        // Swap the processes based on priority
        temp_process = process[i];
        process[i] = process[position];
        process[position] = temp_process;
    }

    // Calculate waiting time for each process
    process[0].waiting_time = 0;  // Waiting time for the first process is 0
    for (int i = 1; i < number_of_process; i++) {
        process[i].waiting_time = 0;
        for (int j = 0; j < i; j++) {
            process[i].waiting_time += process[j].burst_time;
        }
        total += process[i].waiting_time;  // Add to total waiting time
    }

    // Calculate average waiting time
    average_waiting_time = (float)total / number_of_process;
    total = 0;  // Reset total for turnaround time calculation

    // Output: Process name, Burst Time, Waiting Time, Turnaround Time
    printf("\n\nProcess Name \t Burst Time \t Waiting Time \t Turnaround Time\n");
    for (int i = 0; i < number_of_process; i++) {
        process[i].turn_around_time = process[i].burst_time + process[i].waiting_time;
        total += process[i].turn_around_time;  // Add to total turnaround time
        printf("\t%c \t\t %d \t\t %d \t\t %d\n", process[i].process_name, process[i].burst_time,
               process[i].waiting_time, process[i].turn_around_time);
    }

    // Calculate average turnaround time
    average_turnaround_time = (float)total / number_of_process;

    // Output: Average Waiting Time and Average Turnaround Time
    printf("\n\nAverage Waiting Time: %.2f", average_waiting_time);
    printf("\nAverage Turnaround Time: %.2f\n", average_turnaround_time);

    return 0;
}
