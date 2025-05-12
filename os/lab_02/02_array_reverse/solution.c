#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int n;
    if (scanf("%d", &n) != 1 || n < 0)
        return 0;

    int *a = malloc((size_t)n * sizeof(*a));
    if (!a)
        return 0;

    for (int i = 0; i < n; ++i)
        scanf("%d", &a[i]);

    for (int l = 0, r = n - 1; l < r; ++l, --r) {
        int tmp = a[l];
        a[l]   = a[r];
        a[r]   = tmp;
								    }
    for (int i = 0; i < n; ++i)
        printf("%d%c", a[i], i + 1 == n ? '\n' : ' ');

    free(a);
    return 0;
}
