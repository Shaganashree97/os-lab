#include <stdio.h>
#include <limits.h> // Include for INT_MAX

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[], int quantum, int at[]) {
    int rem_bt[n]; // Remaining burst times
    int t = 0; // Current time
    int completed = 0; // Number of completed processes
    
    for (int i = 0; i < n; i++) {
        rem_bt[i] = bt[i];
    }

    // Keep traversing processes in round robin manner until all processes are done
    while (completed < n) {
        int done = 1;
        for (int i = 0; i < n; i++) {
            if (rem_bt[i] > 0 && at[i] <= t) {
                done = 0; // There is a pending process
                if (rem_bt[i] > quantum) {
                    t += quantum;
                    rem_bt[i] -= quantum;
                } else {
                    t += rem_bt[i];
                    wt[i] = t - bt[i] - at[i]; // Calculate waiting time using arrival time
                    rem_bt[i] = 0;
                    completed++;
                }
            }
        }
        if (done == 1) {
            int min_at = INT_MAX;
            for (int i = 0; i < n; i++) {
                if (rem_bt[i] > 0 && at[i] < min_at) {
                    min_at = at[i];
                }
            }
            t = min_at;
        }
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to calculate average time
void findAverageTime(int processes[], int n, int bt[], int quantum, int at[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    findWaitingTime(processes, n, bt, wt, quantum, at);
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
    int burst_time[] = {8, 5, 10, 11};
    int arrival_time[] = {0, 1, 2, 3};
    int quantum = 6;

    findAverageTime(processes, n, burst_time, quantum, arrival_time);
    return 0;
}
