#define _GNU_SOURCE
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
struct sigent { const char *name; int num; };
static const struct sigent short_names[] = {
    {"HUP",  SIGHUP},   {"INT",  SIGINT},   {"QUIT", SIGQUIT},
    {"ILL",  SIGILL},   {"ABRT", SIGABRT},  {"FPE",  SIGFPE},
    {"KILL", SIGKILL},  {"SEGV", SIGSEGV},  {"PIPE", SIGPIPE},
    {"ALRM", SIGALRM},  {"TERM", SIGTERM},  {"USR1", SIGUSR1},
    {"USR2", SIGUSR2},  {"CHLD", SIGCHLD},  {"CONT", SIGCONT},
    {"STOP", SIGSTOP},  {"TSTP", SIGTSTP},  {"TTIN", SIGTTIN},
    {"TTOU", SIGTTOU},  {"BUS",  SIGBUS},   {"POLL", SIGPOLL},
    {"PROF", SIGPROF},  {"SYS",  SIGSYS},   {"TRAP", SIGTRAP},
    {"URG",  SIGURG},   {"VTALRM", SIGVTALRM}, {"XCPU", SIGXCPU},
    {"XFSZ", SIGXFSZ},  {NULL, 0}};
static void handler(int sig){
    printf("[Caught: %s]", strsignal(sig));
    fflush(stdout);}
static int lookup_signal(const char *arg){
    for (const struct sigent *p = short_names; p->name; ++p)
        if (strcasecmp(p->name, arg) == 0) return p->num;

    if (strncasecmp(arg, "SIG", 3) == 0)
        return lookup_signal(arg + 3);

    char *end;
    long n = strtol(arg, &end, 10);
    if (*end == '\0' && n > 0 && n < NSIG) return (int)n;
    return -1;}

int main(int argc, char *argv[]){
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <INTERVAL> <SIGNAL> [SIGNAL ...]\n",
                argv[0]);
        return 1;
    }

    char *end;
    long interval = strtol(argv[1], &end, 10);
    if (*end || interval <= 0) {
        fprintf(stderr, "Invalid interval\n");
        return 1;
    }

    struct sigaction sa = {0};
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);

    for (int i = 2; i < argc; ++i) {
        int s = lookup_signal(argv[i]);
        if (s == -1) {
            fprintf(stderr, "No such signal\n");
            return 1;
        }
        if (sigaction(s, &sa, NULL) == -1) {
            perror("sigaction");
            return 1;
        }
    }

    unsigned long cnt = 0;
    printf("%d: %lu\n", getpid(), cnt++);

    while (1) {
        sleep((unsigned int)interval);
        printf("%d: %lu\n", getpid(), cnt++);
        fflush(stdout);}}
