#include <stdio.h>

// Function to find the waiting time for all processes
void findWaitingTime(int n, int bt[], int wt[], int pr[]) {
    int i, j, pos, temp;
    
    // Sorting burst time and priority in ascending order of priority
    for (i = 0; i < n; i++) {
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (pr[j] < pr[pos]) {
                pos = j;
            }
        }

        // Swap priority
        temp = pr[i];
        pr[i] = pr[pos];
        pr[pos] = temp;

        // Swap burst time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;
    }

    wt[0] = 0; // Waiting time for first process is 0

    // Calculating waiting time
    for (i = 1; i < n; i++) {
        wt[i] = 0;
        for (j = 0; j < i; j++) {
            wt[i] += bt[j];
        }
    }
}

// Function to calculate turn around time
void findTurnAroundTime(int n, int bt[], int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

// Function to calculate average time
void findAverageTime(int processes[], int n, int bt[], int pr[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    findWaitingTime(n, bt, wt, pr);
    findTurnAroundTime(n, bt, wt, tat);

    printf("Processes  Burst time  Priority  Waiting time  Turn around time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("    %d \t\t %d \t\t %d \t\t %d \t\t %d\n", processes[i], bt[i], pr[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn around time = %.2f\n", (float)total_tat / n);
}

// Driver code
int main() {
    int processes[] = {1, 2, 3, 4};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {10, 1, 2, 1};
    int priority[] = {1, 4, 3, 2};

    findAverageTime(processes, n, burst_time, priority);
    return 0;
}
