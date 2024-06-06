#include <stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    int i, j;
    int pos, temp;
    int total_wt = 0;

    // Sorting burst time in ascending order using selection sort
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

        // Swap process IDs
        temp = processes[i];
        processes[i] = processes[pos];
        processes[pos] = temp;
    }

    // Waiting time for first process is 0
    wt[0] = 0;

    // Calculating waiting time
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
        total_wt += wt[i];
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculating turnaround time by adding burst time and waiting time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to calculate average time
void findAverageTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    // Function to find waiting time of all processes
    findWaitingTime(processes, n, bt, wt);

    // Function to find turn around time for all processes
    findTurnAroundTime(processes, n, bt, wt, tat);

    // Display processes along with all details
    printf("Processes   Burst time   Waiting time   Turn around time\n");

    // Calculating total waiting time and total turnaround time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d \t\t %d \t\t %d \t\t %d\n", processes[i], bt[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n", (float)total_tat / (float)n);
}

// Driver code
int main() {
    int processes[] = {1, 2, 3, 4};
    int n = sizeof(processes) / sizeof(processes[0]);

    int burst_time[] = {5,14,8,15};

    findAverageTime(processes, n, burst_time);
    return 0;
}