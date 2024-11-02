#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    // A0 process (main process)
    printf("[%d] A0\n", getpid());
    fflush(stdout);

    pid = fork();
    if (pid) {  // Parent process (A0, acting as B0 after first fork)
        printf("[%d] B0\n", getpid());
        fflush(stdout);

        pid = fork();
        if (pid) {  // Still in the parent process (A0, acting as B1 after second fork)
            printf("[%d] B1\n", getpid());
            fflush(stdout);
            printf("[%d] Bye\n", getpid());  // B1 says Bye
        } else {  // Child process created by second fork (C1)
            printf("[%d] C1\n", getpid());
            fflush(stdout);
            printf("[%d] Bye\n", getpid());  // C1 says Bye
        }
    } else {  // Child process created by the first fork (C0)
        printf("[%d] C0\n", getpid());
        fflush(stdout);
        printf("[%d] Bye\n", getpid());  // C0 says Bye
    }

    return 0;
}

