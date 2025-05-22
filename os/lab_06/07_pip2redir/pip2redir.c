#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void die(const char *m)
{
    perror(m);
    _exit(1);
}

int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "usage: %s cmd1 cmd2 [args]\n", argv[0]);
        return 1;
    }

    int pfd[2];
    if (pipe(pfd) < 0) die("pipe");

    pid_t pid1 = fork();
    if (pid1 < 0) die("fork");

    if (pid1 == 0) {                        
        if (dup2(pfd[1], STDOUT_FILENO) < 0) die("dup2");
        close(pfd[0]);
        close(pfd[1]);
        execlp(argv[1], argv[1], (char *)NULL);
        die("execvp cmd1");
    }

    pid_t pid2 = fork();
    if (pid2 < 0) die("fork");

    if (pid2 == 0) {                         
        if (dup2(pfd[0], STDIN_FILENO) < 0) die("dup2");
        close(pfd[1]);
        close(pfd[0]);
        execvp(argv[2], &argv[2]);           
        die("execvp cmd2");
    }

    close(pfd[0]);
    close(pfd[1]);

    int status;
    while (1) {
        pid_t w = wait(&status);
        if (w < 0) {
            if (errno == ECHILD) break;
            die("wait");
        }
        int code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
        if (w == pid1)
            printf("child 1 exited with %d\n", code);
        else if (w == pid2)
            printf("child 2 exited with %d\n", code);
    }
    return 0;
}

