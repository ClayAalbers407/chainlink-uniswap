/*�����Ҫ��ͷ�ļ�*/
#ifndef C_PROJECT_MAIN_H
#define C_PROJECT_MAIN_H

#include <stdio.h>
#include <Windows.h>
#include <conio.h>
#include <time.h>

/*�궨��*/
#define LIST_HEIGHT 25   //�������а�ĸ߶�
#define LIST_WIDTH 15    //�������а�Ŀ��
#define MAP_HEIGHT 30    //�����ͼ�߶�
#define MAP_WIDTH 100    //�����ͼ���
#define UP 'w'            //�������Ƽ�
#define DOWN 's'        //�������Ƽ�
#define LEFT 'a'        //�������Ƽ�
#define RIGHT 'd'        //�������Ƽ�
int Leaderboard[10];    //���а�
int Leaderboard_count=0; //��¼��ǰ���յ÷ֵ�λ��
char FoodCategory;
/*�ṹ�嶨��*/
typedef struct        //����ʳ����߽ڵ�λ�õĽṹ��
{
    char FoodSpecies[4];
    int x;            //x����λ��
    int y;            //y����λ��
} Food, Snakenode;

typedef struct        //�����ߵĽṹ��
{
    Snakenode snakeNode[1000];   //�߳�������1000���ڵ�
    int length;                  //�߳���
    int speed;                     //���ƶ��ٶ�
} Snake;

/*��������*/
void GotoXY(int, int);    //��궨λ����
void Hide();            //���ع�꺯��
int Menu();                //���˵�����
void Help();            //������Ϣ
void About();            //������Ϣ
void InitMap();            //��ͼ��ʼ��
void PrintFood();        //����ʳ��
int MoveSnake();        //���ƶ�
int IsCorrect();        //��ײ��ײǽ���
void SpeedControl();    //�ٶȿ���
#endif //C_PROJECT_MAIN_H