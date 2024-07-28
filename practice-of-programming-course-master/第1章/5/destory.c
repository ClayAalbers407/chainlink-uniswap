//
// Created by zl on 2021/3/12.
//
static struct Node *Destory(struct Node *head, int n) {
        struct Node *p1, *p2;
        p1 = head;
        p2 = head->next;
        for (int i = 0; i < n - 1; ++i) {
            if (i == (n - 2)) {
                printf("%d ", p2->data);
                p1->next = p2->next;
                free(p2);
            } else {
                p1 = p2;
            }
            p2 = p1->next;
        }
        return p2;
    }
