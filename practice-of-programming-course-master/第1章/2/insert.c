//
// Created by zl on 2021/3/12.
//

#include "main.h"
static void Insert(struct Node *head, int x) {
    struct Node *q=(struct Node *) malloc(sizeof(struct Node));
    q->data = x;
    struct Node *p = head;
    while (p->next && x > p->next->data) {
        p = p->next;
    }
    q->next = p->next;
    p->next = q;
}

