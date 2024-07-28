//
// Created by zl on 2021/4/22.
//
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<time.h>
typedef struct Iris {
    double data[4];
    int ID;
    int anotherID;
    char specie[20];
    double distance;
} Iris;
Iris x[105];//训练集
Iris all[150];//存放所有数据集
Iris y[45];//测试集
#define K 3//定义K
int sub[K];//K个最近的坐标
int main() {
    FILE *fp = fopen("D:\\lenovo_download\\data.txt", "rb");
    if (fp == NULL) {
        printf("不能打开文件");
        return 0;
    }
    //读入数据
    for (int i = 0; i < 150; ++i) {
        fscanf(fp, "%lf,%lf,%lf,%lf,%s", &all[i].data[0], &all[i].data[1], &all[i].data[2], &all[i].data[3],
               all[i].specie);
        if (strcmp(all[i].specie, "Iris-setosa") == 0) {
            all[i].ID = 0;
        }
        if (strcmp(all[i].specie, "Iris-versicolor") == 0) {
            all[i].ID = 1;
        }
        if (strcmp(all[i].specie, "Iris-virginica") == 0) {
            all[i].ID = 2;
        }
    }
    fclose(fp);
    //打乱数据
    int Rand1;
    int Rand2;
    Iris index;
    srand((unsigned int)time(0));
    for (int i = 0; i < 15000; ++i) {
        Rand1 = rand() % 150;
        Rand2 = rand() % 150;
        index = all[Rand2];
        all[Rand2] = all[Rand1];
        all[Rand1] = index;
    }
    for (int i = 0; i < 105; ++i) {
        x[i] = all[i];
    }
    int num = 0;//计数
    for (int i = 105; i < 150; ++i) {
        y[num] = all[i];
        num++;
    }

    //划分测试集
    double distance;
    double min;
    int min_site;
    int count[3];
    int max_count;
    int max_count_site;
    for (int i = 0; i < 45; ++i) {
        count[0] = count[1] = count[2] = 0;
        for (int j = 0; j < 105; ++j) {
            distance = 0;
            for (int k = 0; k < 4; ++k) {
                distance += pow((x[j].data[k] - y[i].data[k]), 2);
            }
            x[j].distance = sqrt(distance);
        }
        for (int j = 0; j < K; ++j) {
            min = x[0].distance;
            min_site = 0;
            for (int k = 1; k < 105; ++k) {
                if (x[k].distance < min) {
                    min = x[k].distance;
                    min_site = k;
                }
            }
            sub[j] = min_site;
            x[min_site].distance = -1;
        }
        for (int j = 0; j < K; ++j) {
            if (x[sub[j]].ID == 0) {
                count[0]++;
            }
            if (x[sub[j]].ID == 1) {
                count[1]++;
            }
            if (x[sub[j]].ID == 2) {
                count[2]++;
            }
        }
        max_count = count[0];
        max_count_site = 0;
        for (int j = 1; j < 3; ++j) {
            if (count[j] > max_count) {
                max_count = count[j];
                max_count_site = j;
            }
        }
        y[i].anotherID = max_count_site;
    }
    for (int i = 0; i < 45; ++i) {
        printf("%d\t%d\n", y[i].ID, y[i].anotherID);
    }
    int right=0;//正确的个数
    for (int i = 0; i < 45; ++i) {
        if(y[i].ID==y[i].anotherID){
            right++;
        }
    }
    printf("正确率为\n%.4f",1.0*right/45);
    return 0;
}