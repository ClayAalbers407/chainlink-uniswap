//
// Created by zl on 2021/3/16.
//

#ifndef C_PROJECT_MAIN_H
#define C_PROJECT_MAIN_H
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
struct lineStack{
    int data;
    struct lineStack *next;
};
struct lineQueue{
    int data;
    struct lineQueue *next;
};
struct lineStack *push(struct lineStack *stack, int a);
struct lineStack *pop(struct lineStack *stack);
#endif //C_PROJECT_MAIN_H
