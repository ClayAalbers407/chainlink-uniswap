#include <stdio.h>
#include "main.h"
#include "method.c"

int main() {
    int a[1000];
    int top = -1;
    int b[1000];
    int front = 0, rear = 0;
    int x;
    scanf("%d", &x);
    while (x != 0) {
        if (x > 0) {
            top = push(a, top, x);
        } else {
            rear = InQueue(b, rear, x);
        }
        scanf("%d", &x);
    }
    while (top != -1) {
        top = pop(a, top);
    }
    printf("(上面为栈，下面为队)\n");
    while (front != rear) {
        front = OutQueue(b, front);
    }
    return 0;
}


