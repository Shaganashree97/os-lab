#include <stdio.h>

// Structure to represent a process
typedef struct {
    int id;         // Process ID
    int bt;         // Burst time
    int pr;         // Priority
    int at;         // Arrival time
} Process;

// Function to find the waiting time for all processes
void findWaitingTime(Process proc[], int n, int wt[]) {
    int rt[n], complete = 0, t = 0, minm = 99999;
    int shortest = 0, finish_time;
    int check = 0;

    // Copy burst times to rt[]
    for (int i = 0; i < n; i++) rt[i] = proc[i].bt;

    while (complete != n) {
        for (int j = 0; j < n; j++) {
            if ((proc[j].at <= t) && (proc[j].pr < minm) && rt[j] > 0) {
                minm = proc[j].pr;
                shortest = j;
                check = 1;
            }
        }

        if (check == 0) {
            t++;
            continue;
        }

        // Reduce remaining time by one
        rt[shortest]--;

        // Update minimum
        minm = rt[shortest];
        if (minm == 0) minm = 99999;

        // If a process gets completely executed
        if (rt[shortest] == 0) {
            complete++;
            check = 0;
            finish_time = t + 1;

            // Calculate waiting time
            wt[shortest] = finish_time - proc[shortest].bt - proc[shortest].at;
            if (wt[shortest] < 0) wt[shortest] = 0;
        }
        t++;
    }
}

// Function to calculate turn around time
void findTurnAroundTime(Process proc[], int n, int wt[], int tat[]) {
    for (int i = 0; i < n; i++) {
        tat[i] = proc[i].bt + wt[i];
    }
}

// Function to calculate average time
void findAverageTime(Process proc[], int n) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;

    findWaitingTime(proc, n, wt);
    findTurnAroundTime(proc, n, wt, tat);

    printf("Processes  Burst time  Arrival time  Priority  Waiting time  Turn around time\n");

    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("    %d \t\t %d \t\t %d \t\t %d \t\t %d \t\t %d\n", proc[i].id, proc[i].bt, proc[i].at, proc[i].pr, wt[i], tat[i]);
    }

    printf("Average waiting time = %.2f\n", (float)total_wt / n);
    printf("Average turn around time = %.2f\n", (float)total_tat / n);
}

// Driver code
int main() {
    Process proc[] = {
        {1, 10, 3, 0},
        {2, 1, 1, 2},
        {3, 2, 4, 1},
        {4, 1, 5, 3}
    };
    int n = sizeof(proc) / sizeof(proc[0]);

    findAverageTime(proc, n);
    return 0;
}
