#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <mqueue.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
int main(int argc,char *argv[]){
    if (argc!= 3) {
        fprintf(stderr, "Usage: %s <mq_name> <message>\n", argv[0]);
        return 1;
    }
    const char *name = argv[1];
    const char *msg  = argv[2];
    mqd_t mqd = mq_open(name, O_WRONLY);
    if (mqd ==(mqd_t)-1) {
        perror("mq_open");
        return 1;
    }
    if (mq_send(mqd, msg, strlen(msg), 1)== -1) {
        perror("mq_send");
        mq_close(mqd);
        return 1;
    }
    if (mq_close(mqd)== -1) {
        perror("mq_close");
        return 1;
    }
    return 0;}
