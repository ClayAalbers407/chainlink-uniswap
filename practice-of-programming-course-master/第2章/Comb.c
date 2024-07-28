//
// Created by zl on 2021/3/26.
//
#include<stdio.h>
#include<string.h>
void comb(int deep,int n,int m,char name[][100],char result[][100],int flag){
    if (deep>n){
        return;
    }
    if (flag==m){
        for (int i = 0; i < m; ++i) {
            printf("%s  ",result[i]);
        }
        printf("\n");
        return;
    }
    strcpy(result[flag++],name[deep]);
    comb(deep+1,n,m,name,result,flag);
    flag--;
    comb(deep+1,n,m,name,result,flag);
}
int main(){
    int n,m,flag=0;

    scanf("%d %d",&n,&m);
    char name[n][100];
    for (int i = 0; i < n; ++i) {
        scanf("%s",name[i]);
    }
    char result[m][100];
    comb(0,n,m,name,result,flag);
    return 0;
}