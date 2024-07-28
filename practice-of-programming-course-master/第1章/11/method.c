//
// Created by zl on 2021/3/16.
//
int push(int a[],int top,int number){
    a[++top]=number;
    return top;
}
int pop(int a[],int top){
    printf("%d ",a[top]);
    top--;
    return top;
}
int InQueue(int b[],int rear,int number){
    b[rear]=number;
    rear++;
    return rear;
}
int OutQueue(int b[], int front) {
    printf("%d ",b[front]);
    front++;
    return front;
}
