//
// Created by zl on 2021/3/12.
//
static void Insert(struct Node *head, int a[],int m) {
    struct Node *p,*tail;
    if (j>=20){
        head->data=a[j-m];
    } else{
        head->data=a[0];
    }
    tail=head;
    for (int i = 1; i < m; ++i) {
        p=(struct Node*)malloc(sizeof (struct Node));
        if (j>=20){
            j++;
            p->data=a[j-m];
        } else{
            p->data=a[i];
        }
        tail->next=p;
        tail=p;
    }
    tail->next=head;
}

