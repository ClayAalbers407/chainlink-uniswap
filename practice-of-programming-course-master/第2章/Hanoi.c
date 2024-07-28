//
// Created by zl on 2021/3/19.
//
#include<stdio.h>
struct Roundel {
    int n;
    char a;
    char b;
    char c;
};
struct Stack{
    struct Roundel Data[10000];
    int top;
} ;

void Push(struct Stack *p, struct Roundel roundel) {
    p->top++;
    p->Data[p->top] = roundel;
}

struct Roundel Pop(struct Stack *p) {
    p->top--;
    return p->Data[p->top + 1];
}

int main() {
    int n;
    scanf("%d", &n);
    struct Roundel p, subProblem1,subProblem2,subProblem3;
    struct Stack s;
    p.n = n;
    p.a = 'A';
    p.b = 'B';
    p.c = 'C';
    s.top = -1;
    Push(&s, p);
    while (s.top != -1) {
        p = Pop(&s);
        if (p.n == 1) {
            printf("%c->%c\n", p.a, p.c);
        } else {
            subProblem1.n = p.n - 1;
            subProblem1.a = p.b;
            subProblem1.b = p.a;
            subProblem1.c = p.c;
            Push(&s, subProblem1);
            subProblem2.n = 1;
            subProblem2.a = p.a;
            subProblem2.b = p.b;
            subProblem2.c = p.c;
            Push(&s, subProblem2);
            subProblem3.n = p.n - 1;
            subProblem3.a = p.a;
            subProblem3.b = p.c;
            subProblem3.c = p.b;
            Push(&s, subProblem3);
        }
    }
    return 0;
}