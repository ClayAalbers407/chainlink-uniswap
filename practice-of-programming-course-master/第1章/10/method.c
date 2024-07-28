//
// Created by zl on 2021/3/16.
//
struct lineStack *push(struct lineStack *stack, int a) {
    struct lineStack *line = (struct lineStack *) malloc(sizeof (struct lineStack));
    line->data = a;
    line->next = stack;
    stack = line;
    return stack;
}

struct lineStack *pop(struct lineStack *stack){
    if (stack) {
        struct lineStack *p=stack;
        stack=stack->next;
        printf("%5d ",p->data);
        free(p);
    }
    return stack;
}
struct lineQueue* InitQueue(){
    struct lineQueue * queue=(struct lineQueue*)malloc(sizeof(struct lineQueue));
    queue->next=NULL;
    return queue;
}
struct lineQueue* InQueue(struct lineQueue * rear,int data){
    struct lineQueue * pQueue=(struct lineQueue*)malloc(sizeof(struct lineQueue));
    pQueue->data=data;
    pQueue->next=NULL;
    rear->next=pQueue;
    rear=pQueue;
    return rear;
}
struct lineQueue *OutQueue(struct lineQueue * top,struct lineQueue * rear){
    struct lineQueue * p=NULL;
    if (top->next==NULL) {
        return rear;
    }
    p=top->next;
    printf("%5d ",p->data);
    top->next=p->next;
    if (rear==p) {
        rear=top;
    }
    free(p);
    return rear;
}