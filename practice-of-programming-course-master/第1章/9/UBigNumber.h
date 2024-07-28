//
// Created by zl on 2021/3/16.
//

#ifndef C_PROJECT_UBIGNUMBER_H
#define C_PROJECT_UBIGNUMBER_H

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
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

#endif //C_PROJECT_UBIGNUMBER_H
