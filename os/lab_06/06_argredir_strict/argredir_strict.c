#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static void die(const char *msg)
{
    perror(msg);
    _exit(1);
}

int main(int argc, char **argv)
{
    if (argc < 4) {
        fprintf(stderr, "usage: %s input output cmd [args]\n", argv[0]);
        return 1;
    }

    int in  = open(argv[1], O_RDONLY);
    if (in < 0) die("open input");

    int out = open(argv[2], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (out < 0) die("open output");

    pid_t pid = fork();
    if (pid < 0) die("fork");

    if (pid == 0) {                 
        if (dup2(in, STDIN_FILENO)  < 0) die("dup2 stdin");
        if (dup2(out, STDOUT_FILENO) < 0) die("dup2 stdout");
        close(in); close(out);
        execvp(argv[3], &argv[3]);
        die("execvp");
    }

    close(in); close(out);


    int status;
    if (waitpid(pid, &status, 0) < 0)
        die("waitpid");
    int rc = 1;

    if (WIFEXITED(status))
        rc = WEXITSTATUS(status);
    printf("received %d\n", rc);
    return rc;
}

