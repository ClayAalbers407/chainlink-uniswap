//
// Created by zl on 2021/3/12.
//
#include "insert.c"
static void link(struct Node *head1, struct Node *head2,struct Node *head3) {
    head1=head1->next;
    while(head1!=NULL){
        Insert(head3,head1->data);
        head1=head1->next;
    }
    head2=head2->next;
    while (head2!=NULL){
        Insert(head3,head2->data);
        head2=head2->next;
    }
}