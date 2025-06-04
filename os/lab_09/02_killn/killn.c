#define _POSIX_C_SOURCE 200809L
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include "signals.h"
typedef struct { const char *name; int num; } sigent;
static sigent *dyn = NULL;
static size_t  dlen = 0;
static void build_dyn(void){
    if (dyn) return;
    dlen = NSIG;
    dyn = calloc(dlen + 1, sizeof(sigent));
    for (int i=1; i<NSIG; ++i) {
        const char *s = strsignal(i);
        if (!s || strncmp(s, "SIG", 3)) continue;
        dyn[i - 1].name=s + 3;
        dyn[i - 1].num=i;
    }}
static int lookup(const char *s)
{
    extern const sigent table[]; 
    for (const sigent *p=table;p->name; ++p)
        if (!strcmp(p->name, s))
            return p->num;
    build_dyn();
    for (sigent *p = dyn; p && p->name; ++p)
        if (!strcmp(p->name, s))
            return p->num;
    return -1;
}
static int badpid(void)  { fprintf(stderr, "Failed to send signal\n"); return 1; }
static int usage(const char *p){ fprintf(stderr,"Usage: %s <PID> <SIGNAL_NAME>\n",p);return 1;}
int main(int argc, char *argv[])
{
    if (argc != 3) return usage(argv[0]);
    char *e = NULL; errno = 0;
    long v = strtol(argv[1], &e, 10);
    if (errno || *e || v <= 0) return badpid();
    pid_t pid = (pid_t)v;
    int sig = lookup(argv[2]);
    if (sig == -1){ fprintf(stderr,"No such signal\n"); return 1; }
    if (kill(pid, sig) == -1) return badpid();
    return 0;
}
