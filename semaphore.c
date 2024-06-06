#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h> // Include for sleep function

sem_t bin_sem;

void* task(void* arg) {
    printf("Thread %ld is waiting to start\n", (long)arg);

    // Wait (P operation) - try to acquire the semaphore
    sem_wait(&bin_sem);
    
    printf("Thread %ld has acquired the semaphore\n", (long)arg);

    // Critical section - only one thread can execute here at a time
    printf("Thread %ld is in the critical section\n", (long)arg);
    sleep(1); // Simulate work
    
    printf("Thread %ld is releasing the semaphore\n", (long)arg);

    // Signal (V operation) - release the semaphore
    sem_post(&bin_sem);
    
    return NULL;
}

int main() {
    pthread_t threads[5];
    
    // Initialize the semaphore as a binary semaphore
    sem_init(&bin_sem, 0, 1); // 1 indicates that the semaphore is available

    // Create multiple threads
    for (long i = 0; i < 5; i++) {
        pthread_create(&threads[i], NULL, task, (void*)i);
    }

    // Wait for all threads to finish
    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    // Destroy the semaphore
    sem_destroy(&bin_sem);

    printf("All tasks are completed\n");

    return 0;
}
