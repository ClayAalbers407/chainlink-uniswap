//
// Created by zl on 2021/3/16.
//
#include "UBigNumber.h"
#include "UBigNumber.c"

int main() {
    struct UBigNumber A, B, C, D;
    A = InputUBN();
    B = InputUBN();
    C = AddUBN(&A, &B);
    D = MinusUBN(&A, &B);
    Normalize(&D);
    PrintUBN(A);
    printf("+");
    PrintUBN(B);
    printf("=");
    PrintUBN(C);
    printf("\n");
    PrintUBN(A);
    printf("-");
    PrintUBN(B);
    printf("=");
    PrintUBN(D);
    DestoryUBN(&A);
    DestoryUBN(&B);
    DestoryUBN(&C);
    DestoryUBN(&D);
    return 0;
}
