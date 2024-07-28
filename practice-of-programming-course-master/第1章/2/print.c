//
// Created by zl on 2021/3/12.
//
static void Print(struct Node *head) {
    head = head->next;
    if (head!=NULL) {
        printf("%d", head->data);
        head = head->next;
    }
    while (head!=NULL) {
        printf("->%d", head->data);
        head = head->next;
    }
    printf("\n");
}
