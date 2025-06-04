#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
typedef struct {
    int   *arr;
    size_t left;
    size_t right;
    long long *sum;
    pthread_mutex_t *mtx;
} task_t;
void *worker(void *arg)
{
    task_t *t=(task_t *)arg;
    long long local = 0;
    for (size_t i = t->left; i < t->right; ++i)
        local+= t->arr[i];
    pthread_mutex_lock(t->mtx);
    *t->sum += local;
    pthread_mutex_unlock(t->mtx);
    return NULL;
}
int main(void)
{
    size_t n;
    if (scanf("%zu", &n) != 1 || n < 16) return 0;
    int *a = malloc(n * sizeof(int));
    if (!a) return 0;
    srand(42u);
    for (size_t i = 0; i < n; ++i) a[i] = rand() % 1000;
    size_t base =n/4;
    size_t rem  = n%4;
    long long sum = 0;
    pthread_mutex_t mtx;
    pthread_mutex_init(&mtx, NULL);
    pthread_t thr[4];
    task_t    t[4];
    size_t pos = 0;
    for (int i = 0; i < 4; ++i) {
        size_t len = base + (i < (int)rem);
        t[i] = (task_t){ .arr = a, .left = pos, .right = pos + len, .sum = &sum, .mtx = &mtx };
        pthread_create(&thr[i], NULL, worker, &t[i]);
        pos += len;
    }
    printf("Array:");
    for (size_t i = 0; i<n; ++i) printf(" %d", a[i]);
    printf("\n");
    for (int i = 0; i <4; ++i) pthread_join(thr[i], NULL);
    printf("Total sum: %lld\n", sum);
    pthread_mutex_destroy(&mtx);
    free(a);
    return 0;
}
