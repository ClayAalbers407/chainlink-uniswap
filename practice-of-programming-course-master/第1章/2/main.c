#include "main.h"
#include "destory.c"
#include "print.c"
#include "link.c"
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
        if (x > 0) {
            Insert(head1, x);
        } else {
            Insert(head2, x);
        }
        scanf("%d", &x);
    }

    Print(head1);
    Print(head2);
    link(head2,head1,head3);
    Print(head3);
    Destory(head1);
    Destory(head2);
    Destory(head3);
    return 0;
}


