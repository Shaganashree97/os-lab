#include <stdio.h>
#include <limits.h>

void findAverageTime(int processes[], int n, int bt[], int at[]) {
    int wt[n], tat[n], rt[n], t = 0, completed = 0;
    int minm = INT_MAX, shortest = 0, finish_time;
    float total_wt = 0, total_tat = 0;

    for (int i = 0; i < n; i++) rt[i] = bt[i];

    while (completed != n) {
        for (int j = 0; j < n; j++) {
            if (at[j] <= t && rt[j] < minm && rt[j] > 0) {
                minm = rt[j];
                shortest = j;
            }
        }

        if (minm == INT_MAX) {
            t++;
            continue;
        }

        rt[shortest]--;
        minm = rt[shortest] ? rt[shortest] : INT_MAX;

        if (rt[shortest] == 0) {
            completed++;
            finish_time = t + 1;
            wt[shortest] = finish_time - bt[shortest] - at[shortest];
            if (wt[shortest] < 0) wt[shortest] = 0;
        }
        t++;
    }

    printf("Processes   Burst time   Arrival time   Waiting time   Turn around time\n");
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
        printf("   %d \t\t %d \t\t %d \t\t %d \t\t %d\n", processes[i], bt[i], at[i], wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", total_wt / n);
    printf("Average turn around time = %.2f\n", total_tat / n);
}

int main() {
    int processes[] = {1, 2, 3, 4};
    int n = sizeof(processes) / sizeof(processes[0]);
    int burst_time[] = {6, 8, 7, 3};
    int arrival_time[] = {0, 1, 2, 3};

    findAverageTime(processes, n, burst_time, arrival_time);
    return 0;
}
