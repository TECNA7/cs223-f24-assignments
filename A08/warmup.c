/**Author : KRIPA LAMICHHANE
 * DATE : 11/1/2024
 * DESCRI[TIPON : WARM UP TO PRINT CHILD AND PARENTS USING FORK
 * **/
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    printf("[%d] A0\n", getpid());
    fflush(stdout);

    pid = fork();
    if (pid) { 
        printf("[%d] B0\n", getpid());
        fflush(stdout);

        pid = fork();
        if (pid) {  
            printf("[%d] B1\n", getpid());
            fflush(stdout);
            printf("[%d] Bye\n", getpid());  
        } else { 
            printf("[%d] C1\n", getpid());
            fflush(stdout);
            printf("[%d] Bye\n", getpid());  
        }
    } else {
        printf("[%d] C0\n", getpid());
        fflush(stdout);
        printf("[%d] Bye\n", getpid()); 
    }

    return 0;
}

