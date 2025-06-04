#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>
struct sigent { const char *name; int num; };
static const struct sigent sigtab[] = {
    {"HUP",  SIGHUP},   {"INT",  SIGINT},   {"QUIT", SIGQUIT},
    {"ILL",  SIGILL},   {"TRAP", SIGTRAP},  {"ABRT", SIGABRT},
    {"BUS",  SIGBUS},   {"FPE",  SIGFPE},   {"USR1", SIGUSR1},
    {"SEGV", SIGSEGV},  {"USR2", SIGUSR2},  {"PIPE", SIGPIPE},
    {"ALRM", SIGALRM},  {"TERM", SIGTERM},  {"CHLD", SIGCHLD},
    {"CONT", SIGCONT},  {"TSTP", SIGTSTP},  {"TTIN", SIGTTIN},
    {"TTOU", SIGTTOU}
};
static int str2sig(const char *s){
    for (size_t i=0;i<sizeof(sigtab)/sizeof(sigtab[0]);++i)
        if (strcmp(s, sigtab[i].name)== 0) return sigtab[i].num;
    return -1;}
static volatile sig_atomic_t quit_sig=-1;
static volatile sig_atomic_t got_quit_sig=0;
static pid_t child_pid =-1;
static void handler(int sig){
    printf("[Caught: %s]", strsignal(sig));
    fflush(stdout);
    if (sig ==quit_sig) {
        got_quit_sig =1;
        if (child_pid> 0) kill(child_pid, SIGTERM);}}
int main(int argc, char *argv[])
{
    if (argc <4) {
        fprintf(stderr,
            "Usage: %s <timeout_sec> <QUIT_SIG> <SIG1> [SIG2 ...]\n",
            argv[0]);
        return 1;
    }
    int timeout = atoi(argv[1]);   
    if (timeout <= 0) {
        fprintf(stderr, "Invalid timeout\n");
        return 1;
    }
    quit_sig = str2sig(argv[2]);
    if (quit_sig == -1 || quit_sig == SIGKILL || quit_sig == SIGSTOP) {
        fprintf(stderr, "No such signal\n");
        return 1;
    }
    child_pid = fork();
    if (child_pid < 0) { perror("fork"); return 1; }
    if (child_pid == 0) {
        while (1) pause();
    }
    struct sigaction sa = { .sa_handler = handler };
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    for (int i= 2; i <argc; ++i) {
        int sig = str2sig(argv[i]);
        if (sig ==-1 || sig == SIGKILL || sig == SIGSTOP) continue;
        sigaction(sig, &sa, NULL);
    }
    int beat = 0;
    const char *quit_name = argv[2]; 
    while (1) {
        printf("Parent heartbeat: %d PID %d\n", beat++, getpid());
        fflush(stdout);
        sleep(timeout);
        if (got_quit_sig) {
            waitpid(child_pid, NULL, 0);
            printf("Exiting gracefully on signal %s\n", quit_name);
            fflush(stdout);
            break;
        }
    }
    return 0;
}
