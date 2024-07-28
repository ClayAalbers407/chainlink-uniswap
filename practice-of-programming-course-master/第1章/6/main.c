#include "main.h"
#include "destory.c"
#include "insert.c"
int main() {
    int flag=0;
    struct Node *head = (struct Node *) malloc(sizeof(struct Node));
    struct Node *head1 = (struct Node *) malloc(sizeof(struct Node));
    head->next = NULL;
    head1->next = NULL;
    int m,n,k;
    scanf("%d %d %d", &m,&n,&k);
    int a[m*100];
    for (int i = 0; i < m; ++i) {
        a[i]=i+1;
    }
    if (n==1){
        for (int i = 0; i < m; ++i) {
            printf("%4d ",a[i]);
        }
    }
    Insert(head,a,m);
    for (int i = 0; i < m ; ++i) {
        head=Destory(head,n,a);
    }
    printf("\n");
    flag=1;
    if (k==1){
        for (int i = 0; i < m; ++i) {
            printf("%4d ",a[i]);
        }
        return 0;
    }
    Insert(head1,a,m);
    for (int i = 0; i < m ; ++i) {
        head1=Destory(head1,k,a);
    }
    return 0;
}


