//
// Created by zl on 2021/3/12.
//
#include "main.h"
static void reverse(struct Node *head){
    struct Node *p,*q;
    p=head->next;
    head->next=NULL;
    while (p!=NULL){
        q=p;
        p=p->next;
        q->next=head->next;
        head->next=q;
    }
}
