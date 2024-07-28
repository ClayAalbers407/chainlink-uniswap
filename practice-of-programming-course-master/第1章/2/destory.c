//
// Created by zl on 2021/3/12.
//
static void Destory(struct Node *head) {
    while (head !=NULL){
        struct Node *q = head->next;
        free(head);
        head=q;
    }
}
