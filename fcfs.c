#include <stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    // Waiting time for first process is 0
    wt[0] = 0;

    // Calculating waiting time for each process
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
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
        printf("   %d \t\t %d \t\t %d \t\t %d\n", (i + 1), bt[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / (float)n);
    printf("Average turn around time = %.2f\n", (float)total_tat / (float)n);
}

// Driver code
int main() {
    int processes[] = {1, 2, 3};
    int n = sizeof(processes) / sizeof(processes[0]);

    int burst_time[] = {10,5,8};

    findAverageTime(processes, n, burst_time);
    return 0;
}