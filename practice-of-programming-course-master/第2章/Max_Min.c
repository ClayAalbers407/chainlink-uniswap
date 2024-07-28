//
// Created by zl on 2021/3/22.
//
#include<stdio.h>

void max_min(int *a, int i, int j, int *max, int *min) {
    int mid;
    int leftmax, leftmin, rightmax, rightmin;
    if (i == j) {
        *max = a[i];
        *min = a[j];
    } else if (i == j - 1) {
        if (a[i] > a[j]) {
            *max = a[i];
            *min = a[j];
        } else {
            *max = a[j];
            *min = a[i];
        }
    } else {
        mid = (i + j) / 2;
        max_min(a, i, mid, &leftmax, &leftmin);
        max_min(a, mid + 1, j, &rightmax, &rightmin);
        if (leftmax > rightmax) {
            *max = leftmax;
        } else {
            *max = rightmax;
        }
        if (leftmin < rightmin) {
            *min = leftmin;
        } else {
            *min = rightmin;
        }
    }
}

int main() {
    int n=0;
    int a[1000];
    while (scanf("%d",&a[n])!=EOF){
        n++;
    }
    int max, min;
    max_min(a, 0, n - 1, &max, &min);
    printf("%d,%d", min ,max);
}