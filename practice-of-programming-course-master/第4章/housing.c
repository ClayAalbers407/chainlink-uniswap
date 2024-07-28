//
// Created by zl on 2021/4/18.
//
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

struct Data {
    double category[14];
};
struct Data data[600];
double correlation[13];
double w[5] = {1, 1, 1, 1, 1};
double a = 0.0001;

int compare(const void *value1, const void *value2) {
    double ret = *(double *) value1 - *(double *) value2;
    if (ret > 0) {
        return -1;
    } else if (ret < 0) {
        return 1;
    }
    return 0;
}

int main() {
    FILE *fp = fopen("D:\\lenovo_download\\housing.txt", "rb");
    if (fp == NULL) {
        printf("不能打开文件");
        return 0;
    }
    for (int i = 0; i < 500; ++i) {
        for (int j = 0; j < 14; ++j) {
            fscanf(fp, "%lf", &data[i].category[j]);
        }
    }
    fclose(fp);

    //相关系数
    double averageX, averageY;
    double sumX, sumY;
    double sum1, sum2, sum3;
    for (int j = 0; j < 13; ++j) {
        sumX = 0, sumY = 0;
        sum1 = 0, sum2 = 0, sum3 = 0;
        for (int i = 0; i < 500; ++i) {
            sumX += data[i].category[j];
            sumY += data[i].category[13];
        }
        averageX = sumX / 500;
        averageY = sumY / 500;
        for (int i = 0; i < 500; ++i) {
            sum1 += (data[i].category[j] - averageX) * (data[i].category[13] - averageY);
            sum2 += pow(data[i].category[j] - averageX, 2);
            sum3 += pow(data[i].category[13] - averageY, 2);
        }
        correlation[j] = sum1 / (sqrt(sum2 * sum3));
    }
    printf("各数据项的相关系数为:\n");
    for (int i = 0; i < 13; ++i) {
        correlation[i] = fabs(correlation[i]);
        printf("%lf\n", correlation[i]);
    }
    qsort(correlation, 13, sizeof(double), compare);
    printf("四个最相关的维度为:\n");
    for (int i = 0; i < 4; ++i) {
        if (i == 0) {
            printf("lstat:%lf\n", correlation[i]);
        }
        if (i == 1) {
            printf("rm:%lf\n", correlation[i]);
        }
        if (i == 2) {
            printf("ptratio:%lf\n", correlation[i]);
        }
        if (i == 3) {
            printf("indus:%lf\n", correlation[i]);
        }
    }
    //归一化
    double min, max;
    for (int i = 0; i < 14; ++i) {
        min = data[0].category[i];
        max = data[0].category[i];
        for (int j = 1; j < 350; ++j) {
            if (data[j].category[i] > max) {
                max = data[j].category[i];
            }
            if (data[j].category[i] < min) {
                min = data[j].category[i];
            }
        }
        for (int j = 0; j < 350; ++j) {
            data[j].category[i] = (data[j].category[i] - min) / (max - min);
        }
    }
//训练
    double sum11, sum22;
    for (int i = 0; i < 100000; ++i) {
        for (int j = 0; j < 5; ++j) {
            sum22 = 0;
            for (int k = 0; k < 350; ++k) {
                sum11 = w[0] + w[1] * data[k].category[12] + w[2] * data[k].category[5] +
                        w[3] * data[k].category[10] + w[4] * data[k].category[2] - data[k].category[13];
                if (j == 0) {
                    sum22 += sum11;
                }
                if (j == 1) {
                    sum22 += sum11 * data[k].category[12];
                }
                if (j == 2) {
                    sum22 += sum11 * data[k].category[5];
                }
                if (j == 3) {
                    sum22 += sum11 * data[k].category[10];
                }
                if (j == 4) {
                    sum22 += sum11 * data[k].category[2];
                }
            }
            w[j] = w[j] - a * sum22 / 350;
        }
    }
    printf("训练100000次结束后的w为\n");
    for (int i = 0; i < 5; ++i) {
        printf("%lf\n", w[i]);
    }
    //反归一化
    double min_y, max_y;
    min_y = data[0].category[13];
    max_y = data[0].category[13];
    for (int j = 1; j < 350; ++j) {
        if (data[j].category[13] > max_y) {
            max_y = data[j].category[13];
        }
        if (data[j].category[13] < min_y) {
            min_y = data[j].category[13];
        }
    }
    double min_x1, max_x1;
    min_x1 = data[0].category[12];
    max_x1 = data[0].category[12];
    for (int j = 1; j < 350; ++j) {
        if (data[j].category[12] > max_x1) {
            max_x1 = data[j].category[12];
        }
        if (data[j].category[12] < min_x1) {
            min_x1 = data[j].category[12];
        }
    }
    double min_x2, max_x2;
    min_x2 = data[0].category[5];
    max_x2 = data[0].category[5];
    for (int j = 1; j < 350; ++j) {
        if (data[j].category[5] > max_x2) {
            max_x2 = data[j].category[5];
        }
        if (data[j].category[5] < min_x2) {
            min_x2 = data[j].category[5];
        }
    }
    double min_x3, max_x3;
    min_x3 = data[0].category[10];
    max_x3 = data[0].category[10];
    for (int j = 1; j < 350; ++j) {
        if (data[j].category[10] > max_x3) {
            max_x3 = data[j].category[10];
        }
        if (data[j].category[10] < min_x3) {
            min_x3 = data[j].category[10];
        }
    }
    double min_x4, max_x4;
    min_x4 = data[0].category[2];
    max_x4 = data[0].category[2];
    for (int j = 1; j < 350; ++j) {
        if (data[j].category[2] > max_x4) {
            max_x4 = data[j].category[2];
        }
        if (data[j].category[2] < min_x4) {
            min_x4 = data[j].category[2];
        }
    }
    //测试
    double sum33 = 0;
    for (int i = 350; i < 500; ++i) {
        sum33 += pow(
                (w[0] * (max_y - min_y) + min_y +
                 w[1] * (data[i].category[12] - min_x1) / (max_x1 - min_x1) * (max_y - min_y) +
                 w[2] * (data[i].category[5] - min_x2) / (max_x2 - min_x2) * (max_y - min_y) +
                 w[3] * (data[i].category[10] - min_x3) / (max_x3 - min_x3) * (max_y - min_y) +
                 w[4] * (data[i].category[2] - min_x4) / (max_x4 - min_x4) * (max_y - min_y) - data[i].category[13]),
                2);
    }
    double rmse = sqrt(sum33 / 150);
    printf("模型的平均误差为:\n");
    printf("%.4lf\n", rmse);

    return 0;
}