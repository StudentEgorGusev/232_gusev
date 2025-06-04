#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mqueue.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
int main(void){
    mqd_t q = mq_open("/mqserver", O_CREAT | O_RDONLY, 0600, NULL);
    if (q ==(mqd_t)-1) {perror("mq_open"); return 1; }
    struct mq_attr attr;
    if (mq_getattr(q, &attr)== -1) {perror("mq_getattr"); mq_close(q); mq_unlink("/mqserver"); return 1;}
    char *buf =malloc(attr.mq_msgsize);
    if (!buf) { perror("malloc"); mq_close(q); mq_unlink("/mqserver"); return 1; }
    while (1) {
        ssize_t n = mq_receive(q, buf, attr.mq_msgsize, NULL);
        if (n== -1) {perror("mq_receive"); free(buf); mq_close(q); mq_unlink("/mqserver"); return 1; }
        buf[n] ='\0';
        if (strcmp(buf, "QUIT")== 0) break;
        printf("Received: %s\n", buf);
        fflush(stdout);}
    free(buf);
    mq_close(q);
    mq_unlink("/mqserver");
    return 0;}
