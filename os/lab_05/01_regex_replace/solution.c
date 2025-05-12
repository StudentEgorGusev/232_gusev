#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 4)
        return 0;
    const char *pat = argv[1];
    const char *src = argv[2];
    const char *rep = argv[3];

    regex_t re;
    if (regcomp(&re, pat, REG_EXTENDED))
        return 0;

    size_t rep_len = strlen(rep);
    size_t cap = strlen(src) + 1;
    char *buf = malloc(cap);
    size_t len = 0;

    const char *cur = src;
    regmatch_t m[1];

    while (regexec(&re, cur, 1, m, 0) == 0) {
        size_t pre = m[0].rm_so;
        size_t need = len + pre + rep_len + 1;
        if (need > cap) {
            cap = need * 2;
            buf = realloc(buf, cap);
        }
        memcpy(buf + len, cur, pre);
        len += pre;
        memcpy(buf + len, rep, rep_len);
        len += rep_len;
        cur += m[0].rm_eo;
    }

    size_t tail = strlen(cur);
    if (len + tail + 1 > cap) {
        cap = len + tail + 1;
        buf = realloc(buf, cap);
    }
    memcpy(buf + len, cur, tail);
    len += tail;
    buf[len] = '\0';

    puts(buf);

    free(buf);
    regfree(&re);
    return 0;
}


