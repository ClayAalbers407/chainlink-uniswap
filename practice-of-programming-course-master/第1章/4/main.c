#include "main.h"
#include "destory.c"
#include "print.c"
#include "split.c"
int main() {
    struct Node *head1 = (struct Node *) malloc(sizeof(struct Node));
    struct Node *head2 = (struct Node *) malloc(sizeof(struct Node));
    struct Node *head3 = (struct Node *) malloc(sizeof(struct Node));
    head1->next = NULL;
    head2->next = NULL;
    head3->next = NULL;
    int x;
    scanf("%d", &x);
    while (x != 0) {
            Insert(head1, x);
        scanf("%d", &x);
    }
    printf("总链表:\n");
    Print(head1);
    Split(head1,head2,head3);
    printf("偶数链表:\n");
    Print(head2);
    printf("奇数链表:\n");
    Print(head3);
    Destory(head1);
    Destory(head2);
    Destory(head3);
    return 0;
}


