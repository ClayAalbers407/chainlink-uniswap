#include "main.h"
#include "destory.c"
#include "insert.c"
int main() {
    struct Node *head = (struct Node *) malloc(sizeof(struct Node));
    head->data=1;
    head->next = NULL;
    int m,n;
    scanf("%d %d", &m,&n);
    if (n==1){
        for (int i = 0; i < m; ++i) {
            printf("%d ",i+1);
        }
        return 0;
    }
    Insert(head,m);
    for (int i = 0; i < m ; ++i) {
        head=Destory(head,n);
    }
    return 0;
}


