//
// Created by zl on 2021/3/12.
//
#include "main.h"
#include "insert.c"
static void Split(struct Node *head1,struct Node *head2,struct Node *head3){
    head1=head1->next;
    while (head1!=NULL){
        if (head1->data%2==0){
            Insert(head2,head1->data);
        } else{
            Insert(head3,head1->data);
        }
        head1=head1->next;
    }
}
