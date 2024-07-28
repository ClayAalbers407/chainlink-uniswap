//
// Created by zl on 2021/3/22.
//
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int flag = 0;
int flag1 = 0;
int flag2 = 0;
struct Node {
    int digit;
    struct Node *prev, *next;
};
struct UBigNumber {
    int digitCount;
    struct Node *pHead, *pTail;
};

struct UBigNumber InputUBN();

void PrintUBN(struct UBigNumber ubn);

struct UBigNumber AddUBN(struct UBigNumber *pA, struct UBigNumber *pB);

struct UBigNumber MinusUBN(struct UBigNumber *pA, struct UBigNumber *pB);

void DestoryUBN(struct UBigNumber *pA);

void InitUBN(struct UBigNumber *pUBN);

void AppendFrontDigit(struct UBigNumber *pUBN, int digit);

void AppendDigit(struct UBigNumber *pUBN, int digit);

void Normalize(struct UBigNumber *pUBN);

struct Node *NewNode();

int CompareUBN(struct UBigNumber ubn1, struct UBigNumber ubn2);

struct UBigNumber MultiplyUBN(struct UBigNumber *pA, struct UBigNumber *pB);

struct UBigNumber MultiplyDigit(struct UBigNumber *pA, int digit2);

struct UBigNumber FetchSub(struct UBigNumber *pA, int start, int end);

struct UBigNumber InputUBN() {
    struct UBigNumber result;
    InitUBN(&result);
    char ch;
    do {
        ch = getchar();
        if (ch == '-') {
            if (flag == 0) {
                flag1++;
            } else {
                flag2++;
            }
        }
        flag++;
    } while (ch < '0' || ch > '9');
    while (ch >= '0' && ch <= '9') {
        AppendDigit(&result, ch - '0');
        ch = getchar();
    }
    Normalize(&result);
    return result;
}

int CompareUBN(struct UBigNumber ubn1, struct UBigNumber ubn2) {
    assert(ubn1.digitCount > 0 && ubn1.pHead->next != NULL);
    assert(ubn2.digitCount > 0 && ubn2.pHead->next != NULL);
    struct Node *p1 = ubn1.pHead->next;
    struct Node *p2 = ubn2.pHead->next;
    if (ubn1.digitCount > ubn2.digitCount) {
        return 1;
    } else if (ubn1.digitCount < ubn2.digitCount) {
        return 0;
    } else {
        while (p1) {
            if (p1->digit > p2->digit) {
                return 1;
            } else if (p1->digit < p2->digit) {
                return 0;
            } else {
                p1 = p1->next;
                p2 = p2->next;
            }
        }
    }
    return 2;
}

void PrintUBN(struct UBigNumber ubn) {
    assert(ubn.digitCount > 0 && ubn.pHead->next != NULL);
    struct Node *p = ubn.pHead->next;
    while (p) {
        printf("%d", p->digit);
        p = p->next;
    }
}

struct UBigNumber AddUBN(struct UBigNumber *pA, struct UBigNumber *pB) {
    struct UBigNumber result, *pResult = &result;
    InitUBN(pResult);
    int iCarry = 0;
    struct Node *p1, *p2;
    p1 = pA->pTail;
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead) {
        int digit = p1->digit + p2->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
        p2 = p2->prev;
    }
    while (p1 != pA->pHead) {
        int digit = p1->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
    }
    while (p2 != pB->pHead) {
        int digit = p2->digit + iCarry;
        iCarry = digit / 10;
        digit %= 10;
        AppendFrontDigit(pResult, digit);
        p2 = p2->prev;
    }
    if (iCarry != 0) {
        AppendFrontDigit(pResult, iCarry);
    }
    return result;
}

struct UBigNumber MinusUBN(struct UBigNumber *pA, struct UBigNumber *pB) {
    struct UBigNumber result, *pResult = &result;
    InitUBN(pResult);
    int iCarry = 0;
    struct Node *p1, *p2;
    p1 = pA->pTail;
    p2 = pB->pTail;
    while (p1 != pA->pHead && p2 != pB->pHead) {
        int digit = p1->digit - p2->digit - iCarry;
        if (digit < 0) {
            iCarry = (digit + 20) / 10;
            digit += 10;
        } else {
            iCarry = digit / 10;
            digit %= 10;
        }
        AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
        p2 = p2->prev;
    }
    while (p1 != pA->pHead) {
        int digit = p1->digit - iCarry;
        if (digit < 0) {
            iCarry = (digit + 20) / 10;
            digit += 10;
        } else {
            iCarry = digit / 10;
            digit %= 10;
        }
        AppendFrontDigit(pResult, digit);
        p1 = p1->prev;
    }
    while (p2 != pB->pHead) {
        int digit = p2->digit - iCarry;
        if (digit < 0) {
            iCarry = (digit + 20) / 10;
            digit += 10;
        } else {
            iCarry = digit / 10;
            digit %= 10;
        }
        AppendFrontDigit(pResult, digit);
        p2 = p2->prev;
    }
    if (iCarry != 0) {
        AppendFrontDigit(pResult, iCarry);
    }
    return result;
}

struct UBigNumber MultiplyUBN(struct UBigNumber *pA, struct UBigNumber *pB) {
    if (pB->digitCount == 1) {
        return MultiplyDigit(pA, pB->pTail->digit);
    } else if (pA->digitCount == 1) {
        return MultiplyDigit(pB, pA->pTail->digit);
    }
    int m = pA->digitCount;
    int n = pB->digitCount;
    int h = (m > n ? m : n) / 2;
    struct UBigNumber a, b, c, d;
    a = FetchSub(pA, 0, m - h);
    b = FetchSub(pA, m - h, m);
    c = FetchSub(pB, 0, n - h);
    d = FetchSub(pB, n - h, n);
    struct UBigNumber z0, z1, z2;
    z2 = MultiplyUBN(&a, &c);
    z0 = MultiplyUBN(&b, &d);
    struct UBigNumber t1, t2, t3, t4, t5, result;
    t1 = AddUBN(&a, &b);
    t2 = AddUBN(&c, &d);
    DestoryUBN(&a);
    DestoryUBN(&b);
    DestoryUBN(&c);
    DestoryUBN(&d);
    t3 = MultiplyUBN(&t1, &t2);
    t4 = AddUBN(&z0, &z2);
    z1 = MinusUBN(&t3, &t4);
    int i;
    for (i = 0; i < 2 * h; i++) {
        AppendDigit(&z2, 0);
    }
    for (i = 0; i < h; i++) {
        AppendDigit(&z1, 0);
    }
    t5 = AddUBN(&z2, &z1);
    result = AddUBN(&t5, &z0);
    DestoryUBN(&z0);
    DestoryUBN(&z1);
    DestoryUBN(&z2);
    DestoryUBN(&t1);
    DestoryUBN(&t2);
    DestoryUBN(&t3);
    DestoryUBN(&t4);
    DestoryUBN(&t5);
    return result;
}
struct UBigNumber MultiplyDigit(struct UBigNumber *pA,int digit2){
    struct UBigNumber result;
    InitUBN(&result);
    if (digit2==0){
        AppendDigit(&result,0);
        return result;
    }
    int iCarry=0;
    struct Node *p1;
    p1=pA->pTail;
    while (p1!=pA->pHead){
        int digit=p1->digit*digit2+iCarry;
        iCarry=digit/10;
        digit%=10;
        AppendFrontDigit(&result,digit);
        p1=p1->prev;
    }
    if (iCarry!=0){
        AppendFrontDigit(&result,iCarry);
    }
    return result;
}
struct UBigNumber FetchSub(struct UBigNumber *pA,int start,int end){
    struct UBigNumber result;
    InitUBN(&result);
    int i=0;
    struct Node *p=pA->pHead->next;
    while (i<start&&p!=NULL){
        p=p->next;
        i++;
    }
    while (i<end&&p!=NULL){
        AppendDigit(&result,p->digit);
        p=p->next;
        i++;
    }
    Normalize(&result);
    return result;
}
void DestoryUBN(struct UBigNumber *pUBN) {
    while (pUBN->pHead != NULL) {
        struct Node *p = pUBN->pHead;
        pUBN->pHead = p->next;
        free(p);
    }

}

void InitUBN(struct UBigNumber *pUBN) {
    struct Node *p = NewNode();
    pUBN->pHead = pUBN->pTail = p;
    p->next = p->prev = NULL;
    pUBN->digitCount = 0;
}

void AppendDigit(struct UBigNumber *pUBN, int digit) {
    if (pUBN->digitCount == 1 && pUBN->pTail->digit == 0) {
        pUBN->pTail->digit = digit;
        return;
    }
    struct Node *p = NewNode();
    p->digit = digit;
    p->next = NULL;
    p->prev = pUBN->pTail;
    pUBN->pTail->next = p;
    pUBN->pTail = p;
    ++pUBN->digitCount;
}

void AppendFrontDigit(struct UBigNumber *pUBN, int digit) {
    struct Node *p = NewNode();
    p->digit = digit;
    p->next = pUBN->pHead->next;
    if (p->next != NULL) {
        p->next->prev = p;
    }
    p->prev = pUBN->pHead;
    pUBN->pHead->next = p;
    if (pUBN->pTail == pUBN->pHead) {
        pUBN->pTail = p;
    }
    ++pUBN->digitCount;
}

void Normalize(struct UBigNumber *pUBN) {
    if (pUBN->digitCount == 0) {
        AppendDigit(pUBN, 0);
    }
    while (pUBN->digitCount > 1 && pUBN->pHead->next->digit == 0) {
        struct Node *p;
        p = pUBN->pHead->next;
        pUBN->pHead->next = p->next;
        p->next->prev = pUBN->pHead;
        free(p);
        --pUBN->digitCount;
    }
}

struct Node *NewNode() {
    struct Node *p;
    p = (struct Node *) malloc(sizeof(struct Node));
    if (p == NULL) {
        printf("Error:out of memory\n");
        exit(-1);
    }
    return p;
}

int main() {
    int boolean;
    struct UBigNumber A, B, C, D,E;
    A = InputUBN();
    B = InputUBN();
    boolean = CompareUBN(A, B);
    if (flag1 == 0 && flag2 == 0) {
        C = AddUBN(&A, &B);
        PrintUBN(C);
        printf("\n");
        if (boolean == 1) {
            D = MinusUBN(&A, &B);
            PrintUBN(D);
            printf("\n");
        } else if (boolean == 0) {
            D = MinusUBN(&B, &A);
            printf("-");
            PrintUBN(D);
            printf("\n");
        } else {
            printf("0");
            printf("\n");
        }
        E=MultiplyUBN(&A,&B);
        PrintUBN(E);
    }
    if (flag1 == 1 && flag2 == 1) {
        C = AddUBN(&A, &B);
        printf("-");
        PrintUBN(C);
        printf("\n");

        if (boolean == 1) {
            D = MinusUBN(&A, &B);
            printf("-");
            PrintUBN(D);
            printf("\n");
        } else if (boolean == 0) {
            D = MinusUBN(&B, &A);
            PrintUBN(D);
            printf("\n");
        } else {
            printf("0");
            printf("\n");
        }
        E=MultiplyUBN(&A,&B);
        PrintUBN(E);
    }
    if (flag1 == 0 && flag2 == 1) {
        if (boolean == 1) {
            C = MinusUBN(&A, &B);
            PrintUBN(C);
            printf("\n");
        } else if (boolean == 0) {
            C = MinusUBN(&B, &A);
            printf("-");
            PrintUBN(C);
            printf("\n");
        } else {
            printf("0");
            printf("\n");
        }
        D = AddUBN(&A, &B);
        PrintUBN(D);
        printf("\n");
        E=MultiplyUBN(&A,&B);
        printf("-");
        PrintUBN(E);
    }
    if (flag1 == 1 && flag2 == 0) {
        if (boolean == 1) {
            C = MinusUBN(&A, &B);
            printf("-");
            PrintUBN(C);
            printf("\n");
        } else if (boolean == 0) {
            C = MinusUBN(&B, &A);
            PrintUBN(C);
            printf("\n");
        } else {
            printf("0");
            printf("\n");
        }
        D = AddUBN(&A, &B);
        printf("-");
        PrintUBN(D);
        printf("\n");
        E=MultiplyUBN(&A,&B);
        printf("-");
        PrintUBN(E);
    }
    DestoryUBN(&A);
    DestoryUBN(&B);
    DestoryUBN(&C);
    DestoryUBN(&D);
    DestoryUBN(&E);
    return 0;
}

