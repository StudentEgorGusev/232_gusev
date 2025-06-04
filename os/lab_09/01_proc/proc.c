#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
int main(int argc, char *argv[])
{
    if (argc!=2) {
        fprintf(stderr, "usage: %s <timeout>\n", argv[0]);
        return 1;
    }
    char *end= NULL;
    errno =0;
    long t = strtol(argv[1], &end, 10);
    if (errno || *end || t <= 0 || t > INT_MAX) {
        fprintf(stderr, "invalid timeout: %s\n", argv[1]);
        return 1;
    }
    int counter = 0;
    pid_t pid = getpid();
    for (;; ++counter) {
        sleep((unsigned)t);
        printf("%d: %d\n", (int)pid, counter);
        fflush(stdout);
    }
     return 0;
}
