//
// Created by zl on 2021/3/23.
//
#include<stdio.h>

void erase(int a[][100], int i, int j, int row, int col,int count) {
    a[i][j] = 0;
    while (i - 1 >= 0 && a[i - 1][j] == count) {
        erase(a, i - 1, j, row, col,count);
    }
    while (i + 1 < row && a[i + 1][j] == count) {
        erase(a, i + 1, j, row, col,count);
    }
    while (j - 1 >= 0 && a[i][j - 1] == count) {
        erase(a, i, j - 1, row, col,count);
    }
    while (j + 1 < col && a[i][j + 1] == count) {
        erase(a, i, j + 1, row, col,count);
    }
}

int getCount(int a[][100], int row, int col,int count) {
    int result = 0;
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            if (a[i][j] == count) {
                result++;
                erase(a, i, j, row, col,count);
            }
        }
    }
    return result;
}

int main() {
    int row, col;
    scanf("%d %d", &row, &col);
    int a[100][100];
    int b[100][100];
    int c[100][100];
    int d[100][100];
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            scanf("%d", &a[i][j]);
        }
    }
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j <col; ++j) {
            b[i][j]=a[i][j];
            c[i][j]=a[i][j];
            d[i][j]=a[i][j];
        }
    }
    printf("%d",getCount(a, row, col,1)+getCount(b, row, col,2)+getCount(c, row, col,3)+getCount(d, row, col,4));
    return 0;
}