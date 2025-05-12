#include <stdio.h>
#include <stdlib.h>

struct node {
    int val;
    struct node *next;
};

static struct node *append(struct node *tail, struct node *n)
{
    if (tail) tail->next = n;
    return n;
}

static struct node *reverse(struct node *head)
{
    struct node *prev = NULL;
    while (head) {
        struct node *next = head->next;
        head->next = prev;
        prev = head;
        head = next;
    }
    return prev;
}

static void print_free(struct node *head)
{
    while (head) {
        printf("%d%c", head->val, head->next ? ' ' : '\n');
        struct node *tmp = head->next;
        free(head);
        head = tmp;
    }
}

int main(void)
{
    struct node *head = NULL, *tail = NULL;
    int x;
    while (scanf("%d", &x) == 1 && x != 0) {
        struct node *n = malloc(sizeof *n);
        if (!n) return 0;
        n->val = x;
        n->next = NULL;
        tail = append(tail, n);
        if (!head) head = n;
    }

    head = reverse(head);
    print_free(head);
    return 0;
}

