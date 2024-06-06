#include <stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum) {
    int rem_bt[n]; // Remaining burst times
    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
    }
    int t = 0; // Current time

    // Keep traversing processes in round robin manner until all processes are done
    while (1) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0) {
                done = 0; // There is a pending process
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i];
                    rem_bt[i] = 0;
                }
            }
        }
        if (done == 1)
            break;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to calculate average time
void findAverageTime(int processes[], int n, int bt[], int quantum) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt, quantum);
    findTurnAroundTime(processes, n, bt, wt, tat);

    printf("Processes   Burst time   Waiting time   Turn around time\n");
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
    int burst_time[] = {8,5,10,11};
    int quantum = 6;

    findAverageTime(processes, n, burst_time, quantum);
    return 0;
}