/**
 * Kripa's Kustomized :
 * Shell Program
 * Author: KRIPA LAMICHHANE
 * Date: 11/1/2024
 * Description: My customized shell with different color and similar to regular shell features
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <pwd.h>
#include <errno.h>

//For coloring different segments
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"

// printing custom prompt 
void print_prompt() {
    char cwd[1024];
    char hostname[1024];
    struct passwd *pw = getpwuid(geteuid());

    gethostname(hostname, sizeof(hostname));
    getcwd(cwd, sizeof(cwd));

    printf(ANSI_COLOR_RED"%s@%s"  ANSI_COLOR_BLUE" --> " ANSI_COLOR_GREEN "%s$" ANSI_COLOR_CYAN "<3333" ANSI_COLOR_MAGENTA ":"ANSI_COLOR_RESET , pw->pw_name, hostname, cwd);
}

int main() {
    char *input;
    //infinte loop
    while (1) {
        // printing the prompt
        print_prompt();

        // checking input
        input = readline("");

        // exit for quitting the program
        if (input == NULL || strcmp(input, "exit") == 0) {
            free(input);
            break;
        }

        // adding input to history if it's not an empty command
        if (strlen(input) > 0) {
            add_history(input);
        }

        // parsing the command and arguments
        char *args[64];
        int i = 0;
        args[i] = strtok(input, " ");
        while (args[i] != NULL) {
            i++;
            args[i] = strtok(NULL, " ");
        }

        pid_t pid = fork();
        if (pid == 0) {
            if (execvp(args[0], args) == -1) {
                perror("ataching error");
            }
            exit(EXIT_FAILURE);
        } else if (pid > 0) {
            int status;
            waitpid(pid, &status, 0);

            if (WIFEXITED(status)) {
                printf("see your execution status for comand: %d\n", WEXITSTATUS(status));
            } else if (WIFSIGNALED(status)) {
                printf("termination %d\n", WTERMSIG(status));
            }
        } else {
            perror("fortk failed");
        }

        // freeing to prevent memory leaks
        free(input);
    }

    return 0;
}

