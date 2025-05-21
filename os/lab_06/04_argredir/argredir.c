#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 4) return 1;
    int in  = open(argv[1], O_RDONLY);
    if (in  < 0) return 1;
    int out = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out < 0) { close(in); return 1; }

    pid_t pid = fork();
    if (pid < 0) return 1;

    if (pid == 0) {
        dup2(in,  STDIN_FILENO);
        dup2(out, STDOUT_FILENO);
        close(in); close(out);
        execvp(argv[3], &argv[3]);
        _exit(1);
    }

    close(in); close(out);
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status))
        printf("received %d\n", WEXITSTATUS(status));
    else
        printf("received -1\n");
    return 0;
}

