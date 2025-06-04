#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
static volatile sig_atomic_t stop_flag= 0;
static void sigint_handler(int sig){
    (void)sig;
    stop_flag =1;}
int main(void) {
    struct sigaction sa= {0};
    sa.sa_handler =sigint_handler;
    sigemptyset(&sa.sa_mask);
    if (sigaction(SIGINT, &sa, NULL)== -1){
        perror("sigaction");
        return 1;}
    struct mq_attr attr ={0};
    attr.mq_maxmsg= 10;
    attr.mq_msgsize=1024;
    mqd_t q = mq_open("/mqsignal",O_CREAT | O_RDONLY, 0600,&attr);
    if (q ==(mqd_t)-1) {
        perror("mq_open");
        return 1;}
    if (mq_getattr(q, &attr) == -1){
        perror("mq_getattr");
        mq_close(q);
        mq_unlink("/mqsignal");
        return 1;}
    char *buf = malloc(attr.mq_msgsize);
    if (!buf) {
        perror("malloc");
        mq_close(q);
        mq_unlink("/mqsignal");
        return 1;}
    while (!stop_flag) {
        ssize_t n =mq_receive(q, buf, attr.mq_msgsize, NULL);
        if (n == -1) {
            if (errno== EINTR) continue;
            perror("mq_receive");
            free(buf);
            mq_close(q);
            mq_unlink("/mqsignal");
            return 1;
        }
        buf[n] = '\0';
        printf("Received: %s\n", buf);
        fflush(stdout);
        if (strcmp(buf, "QUIT") == 0) break;}
    printf("Server stopped\n");
    free(buf);
    if (mq_close(q) == -1){
        perror("mq_close");
        mq_unlink("/mqsignal");
        return 1;}
    if (mq_unlink("/mqsignal") == -1) {
        perror("mq_unlink");
        return 1;}
    return 0;}
