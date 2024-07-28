//
// Created by zl on 2021/3/30.
//
#include<stdio.h>
#include <assert.h>
#include<time.h>
#include<stdlib.h>

typedef struct node {
    int key;
    struct node *next;
} KeyNode;

void copy(int orgin[], int a[], long int len);

//void printMenu();

void BubbleSort(int a[], long int len);

void SelectSort(int a[], long int len);

void InsertionSort(int a[], long int len);

void MergeSort(int a[], int low,long int high, int b[]);

void QuickSort(int a[], int low,long int high);

void CountSort(int a[],long int n, int iCount[],int max, int sorted[]);

void BucketSort(int a[], long int len, int bucket_num);

void RadixSort(int a[], long int len);

void Merge(int a[], int low, int m,long int high, int b[]);

int QuickPass(int a[], int low,long int high);

void RadixCountSort(int index[], int a[], long int len);
int main() {
    int n;
    int begin, end;
    printf("请输入数组规模:(100、1000、10000、100000)\n");
    long int len;
    scanf("%ld", &len);
    int a[len];
    int orgin[len];
    for (long int i = 0; i < len; ++i) {
        orgin[i] = rand() % 100;//规定数据范围
    }
    int max = orgin[0];
    for (long int i = 0; i < len; ++i) {
        if (orgin[i] > max) {
            max = orgin[i];
        }
    }
    int min = orgin[0];
    for (long int i = 0; i < len; ++i) {
        if (orgin[i] < min) {
            min = orgin[i];
        }
    }
    int b[len];
    int iCount[max + 1];
    int sorted[len];
//    printMenu();
    while (1) {
        scanf("%d", &n);
        switch (n) {
            case 1:
                copy(orgin, a, len);
                begin = clock();
                BubbleSort(a, len);
                end = clock();
                printf("%fms\n", (double) end - begin);
                break;
            case 2:
                copy(orgin, a, len);
                begin = clock();
                SelectSort(a, len);
                end = clock();
                printf("%fms\n", (double) end - begin);
                break;
            case 3:
                copy(orgin, a, len);
                begin = clock();
                InsertionSort(a, len);
                end = clock();
                printf("%fms\n", (double) end - begin);
                break;
            case 4:
                copy(orgin, a, len);
                begin = clock();
                MergeSort(a, 0, len, b);
//            for (int i = 0; i < len; ++i) {
//                printf("%d ", a[i]);
//            }
//            printf("\n");
                end = clock();
                printf("%fms\n", (double) end - begin);
                break;
            case 5:
                copy(orgin, a, len);
                begin = clock();
                QuickSort(a, 0, len);
//            for (int i = 0; i < len; ++i) {
//                printf("%d ", a[i]);
//            }
//            printf("\n");
                end = clock();
                printf("%fms\n", (double) end - begin);
                break;
            case 6:
                copy(orgin, a, len);
                begin = clock();
                CountSort(a, len, iCount, max, sorted);
//            for (int i = 0; i < len; ++i) {
//                printf("%d ", sorted[i]);
//            }
//            printf("\n");
                end = clock();
                printf("%fms\n", (double) end - begin);
                break;
            case 7:
                copy(orgin, a, len);
                begin = clock();
                BucketSort(a, len, len / 10);
                end = clock();
                printf("%fms\n", (double) end - begin);
                break;
            case 8:
                copy(orgin, a, len);
                begin = clock();
                RadixSort(a, len);
//            for (int i = 0; i < len; ++i) {
//                printf("%d ", a[i]);
//            }
//            printf("\n");
                end = clock();
                printf("%fms\n", (double) end - begin);
                break;
            default:
                printf("请输入正确序号!\n");
                break;
        }
    }
}

void RadixSort(int a[], long int len) {
    int flag = 1;
    int temp = 1;
    int *radix = (int *) malloc(sizeof(int) * len);
    while (flag) {
        temp = temp * 10;
        flag = 0;
        for (long int i = 0; i < len; ++i) {
            radix[i] = a[i] % temp;
            radix[i] = radix[i] / (temp / 10);
            if (a[i] / temp > 0) {
                flag = 1;
            }
        }
        RadixCountSort(radix, a, len);
    }
}

void RadixCountSort(int index[], int a[], long int len) {
    int *count = (int *) malloc(sizeof(int) * 10);
    for (int i = 0; i < 10; ++i) {
        count[i] = 0;
    }
    for (long int i = 0; i < len; ++i) {
        count[index[i]]++;
    }
    for (int i = 1; i < 10; ++i) {
        count[i] = count[i] + count[i - 1];
    }
    int *sort = (int *) malloc(sizeof(int) * len);
    for (long int i = len - 1; i >= 0; i--) {
        count[index[i]]--;
        sort[count[index[i]]] = a[i];
    }
    for (long int i = 0; i < len; ++i) {
        a[i] = sort[i];
    }
    free(sort);
    free(count);
}

void BucketSort(int a[], long int len, int bucket_num) {
    long int i, j;
    KeyNode **bucket_table = (KeyNode **) malloc(bucket_num * sizeof(KeyNode *));
    for (i = 0; i < bucket_num; i++) {
        bucket_table[i] = (KeyNode *) malloc(sizeof(KeyNode));
        bucket_table[i]->key = 0;
        bucket_table[i]->next = NULL;
    }
    for (j = 0; j < len; j++) {
        KeyNode *node = (KeyNode *) malloc(sizeof(KeyNode));
        node->key = a[j];
        node->next = NULL;
        int index = a[j] / 10;
        KeyNode *p = bucket_table[index];
        if (p->key == 0) {
            bucket_table[index]->next = node;
            (bucket_table[index]->key)++;
        } else {
            while (p->next != NULL && p->next->key <= node->key)
                p = p->next;
            node->next = p->next;
            p->next = node;
            (bucket_table[index]->key)++;
        }
    }
//    KeyNode *k = NULL;
//    for (i = 0; i < bucket_num; i++)
//        for (k = bucket_table[i]->next; k != NULL; k = k->next)
//            printf("%d ", k->key);
//    printf("\n");
}


void CountSort(int a[],long int n, int iCount[],int max, int sorted[]) {
    for (int i = 0; i <= max; ++i) {
        iCount[i] = 0;
    }
    for (int i = 0; i < n; ++i) {
        ++iCount[a[i]];
    }
    int iStartPos = 0;
    for (int i = 0; i <= max; ++i) {
        int iNextPos = iStartPos + iCount[i];
        iCount[i] = iStartPos;
        iStartPos = iNextPos;
    }
    assert(iStartPos == n);
    for (int i = 0; i < n; ++i) {
        sorted[iCount[a[i]]++] = a[i];
    }
}

void QuickSort(int a[], int low,long int high) {
    if (low >= high) {
        return;
    }
    int pivot = QuickPass(a, low, high);
    QuickSort(a, low, pivot - 1);
    QuickSort(a, pivot + 1, high);
}

int QuickPass(int a[], int low, long int high) {
    int x = a[low];
    while (low < high) {
        while (low < high && x <= a[high]) {
            high--;
        }
        if (low == high) {
            break;
        }
        a[low++] = a[high];
        while (low < high && x >= a[low]) {
            low++;
        }
        if (low == high) {
            break;
        }
        a[high--] = a[low];
    }
    a[low] = x;
    return low;
}

void MergeSort(int a[], int low,long int high, int b[]) {
    if (low >= high) {
        return;
    }
    int m = (low + high) / 2;
    MergeSort(a, low, m, b);
    MergeSort(a, m + 1, high, b);
    Merge(a, low, m, high, b);
    for (int i = low; i <= high; ++i) {
        a[i] = b[i];
    }

}

void Merge(int a[], int low, int m,long int high, int b[]) {
    int i = low;
    int j = m + 1;
    int k = i;
    while (i <= m && j <= high) {
        if (a[i] <= a[j]) {
            b[k++] = a[i++];
        } else {
            b[k++] = a[j++];
        }
    }
    while (i <= m) {
        b[k++] = a[i++];
    }
    while (j <= high) {
        b[k++] = a[j++];
    }
}

void InsertionSort(int a[], long int len) {
    int x, j;
    for (long int i = 0; i < len; ++i) {
        x = a[i];
        j = i - 1;
        while (j >= 0 && x < a[j]) {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = x;
    }
//    for (int i = 0; i < len; ++i) {
//        printf("%d ", a[i]);
//    }
//    printf("\n");
}

void SelectSort(int a[],long int len) {
    int temp;
    for (long int i = 0; i < len - 1; ++i) {
        for (long int j = i + 1; j < len; ++j) {
            if (a[i] > a[j]) {
                temp = a[j];
                a[j] = a[i];
                a[i] = temp;
            }
        }
    }
//    for (int i = 0; i < len; ++i) {
//        printf("%d ", a[i]);
//    }
//    printf("\n");
}

void BubbleSort(int a[], long int len) {
    int temp;
    for (long int i = 0; i < len - 1; ++i) {
        for (long int j = 0; j < len - i - 1; ++j) {
            if (a[j] > a[j + 1]) {
                temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
            }
        }
    }
//    for (int i = 0; i < len; ++i) {
//        printf("%d ", a[i]);
//    }
//    printf("\n");
}

void printMenu() {
    printf("请选择排序算法:\n1.冒泡排序 2.选择排序 3.插入排序 4.归并排序 5.快速排序 6.计数排序 7.桶排序 8.基数排序\n");
}

void copy(int orgin[], int a[],long int len) {
    for (long int i = 0; i < len; ++i) {
        a[i] = orgin[i];
    }
}