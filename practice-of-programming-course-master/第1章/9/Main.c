//
// Created by zl on 2021/3/16.
//
#include "UBigNumber.h"
#include "UBigNUmber.c"

int main() {
    int boolean;
    struct UBigNumber A, B, C, D;
    A = InputUBN();
    B = InputUBN();
    boolean = CompareUBN(A, B);
    if (flag1 == 0 && flag2 == 0) {
        C = AddUBN(&A, &B);
        printf("add:");
        PrintUBN(C);
        printf("\n");
        if (boolean == 1) {
            D = MinusUBN(&A, &B);
            printf("minus:");
            PrintUBN(D);
        } else if (boolean == 0) {
            D = MinusUBN(&B, &A);
            printf("minus:-");
            PrintUBN(D);
        } else {
            printf("minus:0");
        }
    }
    if (flag1 == 1 && flag2 == 1) {
        C = AddUBN(&A, &B);
        printf("add:-");
        PrintUBN(C);
        printf("\n");

        if (boolean == 1) {
            D = MinusUBN(&A, &B);
            printf("minus:-");
            PrintUBN(D);
        } else if (boolean == 0) {
            D = MinusUBN(&B, &A);
            printf("minus:");
            PrintUBN(D);
        } else {
            printf("minus:0");
        }
    }
    if (flag1 == 0 && flag2 == 1) {
        if (boolean == 1) {
            C = MinusUBN(&A, &B);
            printf("add:");
            PrintUBN(C);
            printf("\n");
        } else if (boolean == 0) {
            C = MinusUBN(&B, &A);
            printf("add:-");
            PrintUBN(C);
            printf("\n");
        } else {
            printf("add:0");
            printf("\n");
        }
        D = AddUBN(&A, &B);
        printf("minus:");
        PrintUBN(D);
    }
    if (flag1 == 1 && flag2 == 0) {
        if (boolean == 1) {
            C = MinusUBN(&A, &B);
            printf("add:-");
            PrintUBN(C);
            printf("\n");
        } else if (boolean == 0) {
            C = MinusUBN(&B, &A);
            printf("add:");
            PrintUBN(C);
            printf("\n");
        } else {
            printf("add:0");
            printf("\n");
        }
        D = AddUBN(&A, &B);
        printf("minus:-");
        PrintUBN(D);
    }
    DestoryUBN(&A);
    DestoryUBN(&B);
    DestoryUBN(&C);
    DestoryUBN(&D);
    return 0;
}
