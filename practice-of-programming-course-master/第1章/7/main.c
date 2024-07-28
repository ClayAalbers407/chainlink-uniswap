#include "main.h"
#include "destory.c"
#include "insert.c"
int main() {
    int m,n;
    scanf("%d %d", &m,&n);
    int a[m*100];
    for (int i = 0; i < m; ++i) {
        a[i]=i+1;
    }
    while (n>0){
        struct Node *head = (struct Node *) malloc(sizeof(struct Node));
        head->next = NULL;
        Insert(head,a,m);
        if (n==1){
            for (int i = 0; i < m; ++i) {
                printf("%4d ",a[i]);
            }
        }
        for (int i = 0; i < m ; ++i) {
            head=Destory(head,n,a);
        }
        scanf("%d",&n);
        printf("\n");
    }
    return 0;
}


