#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent process (PID %d) is running\n", getpid());
        wait(NULL); // Wait for the child process to complete
        printf("Parent process detected that the child process has exited\n");
    } else if (pid == 0) {
        // Child process
        printf("Child process (PID %d) is running\n", getpid());
        sleep(5);
        printf("Child process is exiting\n");
        exit(0);
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}
