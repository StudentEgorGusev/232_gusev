#include <stdio.h>
#include <stdlib.h>

static inline size_t idx(size_t row, size_t col, size_t ncols)
{

    return row * ncols + col;
}

int main(void)
{
    size_t n, m;                       
    if (scanf("%zu %zu", &n, &m) != 2 || n == 0 || m == 0)
        return 0;


    int *a = malloc(n * m * sizeof(*a));
    if (!a)
        return 0;

    for (size_t i = 0; i < n * m; ++i)
        scanf("%d", &a[i]);

    int *b = malloc(m * n * sizeof(*b));
    if (!b) {
        free(a);
        return 0;
    }


    for (size_t i = 0; i<n; ++i)
        for (size_t j = 0; j < m; ++j)
            b[idx(j, i, n)] = a[idx(i, j, m)];


    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j) {
            printf("%d", b[idx(i, j, n)]);
            putchar(j + 1 == n ? '\n' : ' ');
        }
    }
    free(b);
    free(a);
    return 0;
}

