#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void)
{
    pid_t pid1 = fork();
    if (pid1 < 0) return 1;

    if (pid1 == 0) {                  
        pid_t pid2 = fork();
        if (pid2 < 0) return 1;

        if (pid2 == 0) {              
            printf("Hello from Child2\n");
            fflush(stdout);
            _exit(0);
        }
        waitpid(pid2, NULL, 0);
        printf("Hello from Child1\n");
        fflush(stdout);
        _exit(0);
    }

    waitpid(pid1, NULL, 0);
    printf("Hello from Parent\n");
    fflush(stdout);
    return 0;
}

