#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    if (argc < 3) return 1;
    int fd = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) return 1;

    pid_t pid = fork();
    if (pid < 0) return 1;
    if (pid == 0) {
        if (dup2(fd, STDOUT_FILENO) < 0) _exit(1);
        close(fd);
        argv[argc - 1] = NULL;
        execvp(argv[1], &argv[1]);
        _exit(1);
    }
    close(fd);
    int status;
    waitpid(pid, &status, 0);
    return WIFEXITED(status) ? WEXITSTATUS(status) : 1;
}

