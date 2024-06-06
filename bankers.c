#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES] = {3, 3, 2}; // Initial available resources
int max[MAX_PROCESSES][MAX_RESOURCES] = { // Maximum demand of each process
    {7, 5, 3},
    {3, 2, 2},
    {9, 0, 2},
    {2, 2, 2},
    {4, 3, 3}
};
int allocation[MAX_PROCESSES][MAX_RESOURCES] = { // Currently allocated resources
    {0, 1, 0},
    {2, 0, 0},
    {3, 0, 2},
    {2, 1, 1},
    {0, 0, 2}
};
int need[MAX_PROCESSES][MAX_RESOURCES]; // Resources needed to complete

// Function to calculate the need matrix
void calculateNeed() {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        for (int j = 0; j < MAX_RESOURCES; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// Function to check if the system is in a safe state and to find the safe sequence
bool isSafe(int safeSequence[]) {
    bool finish[MAX_PROCESSES] = {0};
    int work[MAX_RESOURCES];
    for (int i = 0; i < MAX_RESOURCES; i++) {
        work[i] = available[i];
    }

    int count = 0;

    while (count < MAX_PROCESSES) {
        bool found = false;
        for (int i = 0; i < MAX_PROCESSES; i++) {
            if (!finish[i]) {
                bool canFinish = true;
                for (int j = 0; j < MAX_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        canFinish = false;
                        break;
                    }
                }
                if (canFinish) {
                    for (int j = 0; j < MAX_RESOURCES; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }
        if (!found) {
            return false;
        }
    }

    return true;
}

// Function to request resources for a process
bool requestResources(int process, int request[]) {
    for (int i = 0; i < MAX_RESOURCES; i++) {
        if (request[i] > need[process][i]) {
            printf("Error: Process has exceeded its maximum claim.\n");
            return false;
        }
        if (request[i] > available[i]) {
            printf("Error: Resources are not available.\n");
            return false;
        }
    }

    for (int i = 0; i < MAX_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process][i] += request[i];
        need[process][i] -= request[i];
    }

    int safeSequence[MAX_PROCESSES];
    if (isSafe(safeSequence)) {
        printf("The system is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < MAX_PROCESSES; i++) {
            printf("P%d ", safeSequence[i]);
        }
        printf("\n");
        return true;
    } else {
        printf("The system is not in a safe state. Rolling back.\n");
        for (int i = 0; i < MAX_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process][i] -= request[i];
            need[process][i] += request[i];
        }
        return false;
    }
}

int main() {
    calculateNeed();

    int process = 1;
    int request[] = {1, 0, 2};

    if (requestResources(process, request)) {
        printf("Request has been granted.\n");
    } else {
        printf("Request cannot be granted.\n");
    }

    return 0;
}