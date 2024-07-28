//
// Created by zl on 2021/3/16.
//
#include "main.h"
#include "method.c"
int main(){
    struct lineStack *stack=NULL;
    struct lineQueue *top,*rear;
    top=rear=InitQueue();
    int x;
    scanf("%d",&x);
    while (x!=0){
        if (x>0){
            stack=push(stack, x);
        } else{
            rear=InQueue(rear, x);
        }
        scanf("%d",&x);
    }
    if (!stack){
        goto label;
    }
    while (stack){
        stack=pop(stack);
    }
    if (rear==top){
        return 0;
    }
    printf("\n");
    label:
    while (rear!=top){
        rear=OutQueue(top, rear);
    }
    return 0;
}

