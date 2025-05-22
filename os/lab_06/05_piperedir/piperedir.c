#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 3) return 1;           

    int p[2];
    if (pipe(p) < 0) return 1;

    pid_t c1 = fork();
    if (c1 < 0) return 1;
    if (c1 == 0) {                    
        dup2(p[1], STDOUT_FILENO);
        close(p[0]); close(p[1]);
        execlp(argv[1], argv[1], (char*)NULL);
        _exit(1);
    }

    pid_t c2 = fork();
    if (c2 < 0) return 1;
    if (c2 == 0) {                   
        dup2(p[0], STDIN_FILENO);
        close(p[1]); close(p[0]);
        execvp(argv[2], &argv[2]);    
        _exit(1);
    }

    close(p[0]); close(p[1]);
    int st;
    waitpid(c1, &st, 0);
    waitpid(c2, &st, 0);
    return 0;
}

