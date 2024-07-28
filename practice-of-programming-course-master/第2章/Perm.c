//
// Created by zl on 2021/3/26.
//
#include<stdio.h>
void perm(int array[],int deep,int n,int result[],int flag[]){
    if (deep>n){
        return;
    }
    if (deep==n){
        for (int i = 0; i < n; ++i) {
            printf("%d",result[i]);
        }
        printf("\n");
    }
    for (int i = 0; i < n; ++i) {
        if (flag[i]==0){
            flag[i]=1;
            result[deep]=array[i];
            perm(array, deep+1, n,result,flag);
            flag[i]=0;
        }
    }
}
int main(){
    int n;
    scanf("%d",&n);
    int array[n];
    int result[n];
    int flag[10]={0};
    for (int i = 0; i < n; ++i) {
        array[i]= i + 1;
    }
    perm(array, 0, n,result,flag);
    return 0;
}
