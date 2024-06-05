#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();

    if (pid > 0) {
        // Parent process
        printf("Parent process (PID %d) is exiting\n", getpid());
        exit(0);
    } else if (pid == 0) {
        // Child process
        sleep(10); // Give time for the parent to exit
        printf("Orphan child process (PID %d) is now adopted by init/systemd\n", getpid());
    } else {
        perror("fork failed");
        exit(1);
    }

    return 0;
}
