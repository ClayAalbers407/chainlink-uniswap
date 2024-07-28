#include "snake.h"

/*ȫ�ֱ�������*/
Snake snake;    //�����߽ṹ�����
Food food;        //����ʳ��ṹ�����
char now_Dir = RIGHT;    //��ǰ��ͷ����
char direction = RIGHT; //Ԥ����ͷ����

/*���˵�ʵ��*/
int Menu() {
    GotoXY(40, 12);                 //��λ���λ��
    printf("��ӭ����̰����С��Ϸ");
    GotoXY(43, 14);
    printf("1.��ʼ��Ϸ");
    GotoXY(43, 16);
    printf("2.����");
    GotoXY(43, 18);
    printf("3.����");
    GotoXY(43, 20);
    printf("����������˳���Ϸ");
    Hide();                           //���ع��
    char ch;
    int result = 0;
    ch = _getch();                //�����û�����Ĳ˵�ѡ��
    switch (ch) {                //����ѡ�����÷��ؽ��ֵ
        case '1':
            result = 1;
            break;
        case '2':
            result = 2;
            break;
        case '3':
            result = 3;
            break;
    }
    system("cls");                //����ϵͳ����cls�����������
    return result;
}

//qsort����ʵ��
int comp(const void *a, const void *b) {
    return *(int *) b - *(int *) a;
}

//��궨λ����������궨λ��(x,y)����λ��
void GotoXY(int x, int y) {
    HANDLE hout;
    COORD cor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(hout, cor);
}

/*���ع��*/
void Hide() {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cor_info = {1, 0};
    SetConsoleCursorInfo(hout, &cor_info);
}


/*���ڲ˵�ʵ��*/
void About() {
    GotoXY(30, 12);
    printf("���ݵ��ӿƼ���ѧ--��������ۺ�ʵ������");
    GotoXY(43, 14);
    printf("̰����-����̨��Ϸ");
    GotoXY(43, 16);
    printf("������������ϼ��˵�");
    Hide();        //���ع��
    char ch = _getch();
    system("cls");
}

/*�����˵�ʵ��*/
void Help() {
    GotoXY(40, 12);
    printf("w ��");
    GotoXY(40, 14);
    printf("s ��");
    GotoXY(40, 16);
    printf("a ��");
    GotoXY(40, 18);
    printf("d ��");
    GotoXY(40, 20);
    printf("����ײ�������ײǽʱ��Ϸ����");
    GotoXY(45, 22);
    printf("������������ϼ��˵�");
    Hide();        //���ع��
    char ch = _getch();
    system("cls");
}

/*��ʼ����ͼ����*/
void InitMap() {
    Hide();                    //���ع��
    //������ͷλ���ڵ�ͼ����
    snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
    snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);      //������ƶ�����ͷλ��
    printf("@");                //��ӡ��ͷ
    snake.length = 3;        //�����߳���ʼֵΪ3��
    snake.speed = 250;        //�����߳�ʼ�ƶ��ٶ�Ϊ250
    now_Dir = RIGHT;            //��ǰ��ͷ����
    //��ʾ����
    for (int i = 1; i < snake.length; i++) {
        //���������������λ�ú���ͷλ����ͬ
        snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
        //��������ĺ�����λ�ã���������ͷ�����,���Ժ��������μ�1
        snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
        GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);    //�ƶ���굽����λ��
        printf("0");        //��ӡ����
    }
    //���ɵ�ͼ���±߽�
    for (int i = 0; i < MAP_WIDTH; i++) {
        GotoXY(i, 0);
        printf("��");
        GotoXY(i, MAP_HEIGHT - 1);
        printf("��");
    }
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        GotoXY(0, i);
        printf("��");
        GotoXY(MAP_WIDTH - 1, i);
        printf("��");
    }

    for (int i = 10; i < 21; i++) {
        GotoXY(30, i);
        printf("|");
        GotoXY(70, i);
        printf("|");
    }
    for (int i = 30; i < 51; i++) {
        GotoXY(i, 20);
        printf("-");
    }

    for (int i = 50; i < 71; i++) {
        GotoXY(i, 10);
        printf("-");
    }


    //����ʳ��
    PrintFood();
    //�÷�˵��
    qsort(Leaderboard, 10, sizeof(int), comp);
    GotoXY(105, 0);
    printf("��ǰ�÷�:0");
    GotoXY(105, 2);
    printf("�������а�");
    //�������а����±߽�
    for (int i = 0; i < LIST_WIDTH; i++) {
        GotoXY(101 + i, 3);
        printf("��");
        GotoXY(101 + i, 2 + LIST_HEIGHT);
        printf("��");
    }
    //�������а����ұ߽�
    for (int i = 1; i < LIST_HEIGHT - 1; i++) {
        GotoXY(100, 3 + i);
        printf("��");
        GotoXY(101 + LIST_WIDTH, 3 + i);
        printf("��");
    }
    int temp = 0;
    for (int i = 0; i < sizeof(Leaderboard) / sizeof(Leaderboard[0]); ++i) {
        temp = temp + 2;
        GotoXY(101, 4 + temp);
        printf("  NO.%d : %d ��", i + 1, Leaderboard[i]);
    }
}

/*����ʳ�ﺯ��*/
void PrintFood() {
    int flag = 1;
    while (flag) {
        flag = 0;
        //���������ʳ������λ��
        food.x = rand() % (MAP_WIDTH - 2) + 1;
        food.y = rand() % (MAP_HEIGHT - 2) + 1;
        //ѭ���ж�ʳ��λ���Ƿ���ߵ�λ���ص�������ص�����Ҫ��������ʳ��λ��
        for (int k = 0; k <= snake.length - 1; k++) {
            if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y) {
                flag = 1;                //λ�����ص�����Ҫ����ѭ��
                break;
            }
        }
        if ((food.x == 30 && 10 <= food.y && food.y <= 20) ||
            (food.x == 70 && 10 <= food.y && food.y <= 20) ||
            (food.y == 20 && 30 <= food.x && food.x <= 50) ||
            (food.y == 10 && 50 <= food.x && food.x <= 70)) {
            flag = 1;
            continue;
        }
    }
    GotoXY(food.x, food.y);
    food.FoodSpecies[0] = '#', food.FoodSpecies[1] = '$', food.FoodSpecies[2] = '&', food.FoodSpecies[3] = '*';
    FoodCategory = food.FoodSpecies[rand() % 4];
    printf("%c", FoodCategory);
}


/*���ƶ�����ʵ��,����ֵΪ1��ʾ�����ƶ���Ϊ0��ʾֹͣ�ƶ�*/
int MoveSnake() {
    Snakenode temp;
    int flag = 0;
    temp = snake.snakeNode[snake.length - 1];            //��¼��β
    for (int i = snake.length - 1; i >= 1; i--)
        snake.snakeNode[i] = snake.snakeNode[i - 1];    //������������ǰ�ƶ�һ��λ��
    GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
    printf("0");            //ǰ�������ӡһ����������������Ҫ��ӡ
    //��Ӧ�����޸�
    if (_kbhit()) {            //�������뷵��1���Ǽ������뷵��0
        direction = _getch();
        switch (direction) {
            case UP:  //����w��
                if (now_Dir != DOWN)        //�����ͷ���£��������ƶ��ļ�wʱ��������
                    now_Dir = direction;
                break;
            case DOWN:  //����s��
                if (now_Dir != UP)            //�����ͷ���ϣ��������ƶ��ļ�sʱ��������
                    now_Dir = direction;
                break;
            case LEFT:  //����a��
                if (now_Dir != RIGHT)        //�����ͷ���ң��������ƶ��ļ�aʱ��������
                    now_Dir = direction;
                break;
            case RIGHT:  //����d��
                if (now_Dir != LEFT)        //�����ͷ���󣬰������ƶ��ļ�dʱ��������
                    now_Dir = direction;
                break;
        }
    }
    switch (now_Dir) {                    //�������ڵķ����޸���ͷ��λ��
        case UP:
            snake.snakeNode[0].y--;
            break;        //�����ƶ�
        case DOWN:
            snake.snakeNode[0].y++;
            break;        //�����ƶ�
        case LEFT:
            snake.snakeNode[0].x--;
            break;        //�����ƶ�
        case RIGHT:
            snake.snakeNode[0].x++;
            break;    //�����ƶ�
    }
    //��ӡ��ͷ
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
    printf("@");
    //�ж��Ƿ�Ե�ʳ������ͷ��λ�ú�ʳ���λ����ͬ��ʾ�Ե�ʳ��
    if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
        flag = 1;            //flagΪ1��ʾ�Ե�ʳ�Ϊ0��ʾû�гԵ�ʳ��
        if (FoodCategory == '#') {
            snake.length++;//�Ե�ʳ��߳���1
            snake.snakeNode[snake.length - 1] = temp;    //�Ե�ʳ���β��һ��
        }
        if (FoodCategory == '$') {
            /*
             * �Ե�'$'��β������
             * */
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
        }
        if (FoodCategory == '&') {
            /*
             * �Ե�'&'��β������
             * */
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
        }
        if (FoodCategory == '*') {
            /*
             * �Ե�'*'��β���Ľ�
             * */
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
        }
    }
    //����ߴ�ʱ״̬
    //û�Ե�ʳ��ʱ����ԭ������β��ӡһ���ո�ȥ��ԭ������β
    if (!flag) {
        GotoXY(temp.x, temp.y);
        printf(" ");
    } else {            //�Ե�ʳ�����Ҫ�ڵ�ͼ�����¸���һ��ʳ��
        PrintFood();
        GotoXY(105, 0);
        printf("��ǰ�÷�:%d", snake.length - 3);    //��ӡ�÷֣��÷�Ϊ�߳���ԭʼ����3
    }
    //�ж��Ƿ�����
    if (!IsCorrect()) {        //�����ײ��ײǽ���������Ļ����ӡ���յ÷֣���Ϸ����
        system("cls");
        GotoXY(45, 14);
        printf("���յ÷֣�%d", snake.length - 3);
        Leaderboard[Leaderboard_count++] = snake.length - 3;
        GotoXY(45, 16);
        printf("�����ˣ�");
        GotoXY(45, 18);
        printf("��������������˵�");
        char c = _getch();
        system("cls");
        return 0;
    }
    //�����ٶ�
    SpeedControl();
    Sleep(snake.speed);        //�ѽ��̹���һ��ʱ�䣬���ڿ������ƶ����ٶ�
    return 1;
}

/*�ж��Ƿ���ײ��ײǽ,����ֵΪ0��ʾ��ײ��ײǽ������Ϊ1*/
int IsCorrect() {
    if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_WIDTH - 1 ||
        snake.snakeNode[0].y == MAP_HEIGHT - 1) //�ж���ͷ�Ƿ�ײǽ
        return 0;
    if ((snake.snakeNode[0].x == 30 && 10 <= snake.snakeNode[0].y && snake.snakeNode[0].y <= 20) ||
        (snake.snakeNode[0].x == 70 && 10 <= snake.snakeNode[0].y && snake.snakeNode[0].y <= 20) ||
        (snake.snakeNode[0].y == 20 && 30 <= snake.snakeNode[0].x && snake.snakeNode[0].x <= 50) ||
        (snake.snakeNode[0].y == 10 && 50 <= snake.snakeNode[0].x && snake.snakeNode[0].x <= 70))
        return 0;
    for (int i = 1; i < snake.length; i++) {   //�ж���ͷ�Ƿ�������ص����ص���ʾ��ײ
        if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y) {
            GotoXY(snake.snakeNode[snake.length - 1].x, snake.snakeNode[snake.length - 1].y);
            printf(" ");
            snake.length--;
            GotoXY(105, 0);
            printf("��ǰ�÷�:%d", snake.length - 3);
        }
    }
    return 1;
}

/*�ٶȵ�������*/
void SpeedControl() {
    switch (snake.length) {        //�����߳������ߵ��ƶ��ٶ�
        case 6:
            snake.speed = 200;
            break;
        case 9:
            snake.speed = 180;
            break;
        case 12:
            snake.speed = 160;
            break;
        case 15:
            snake.speed = 140;
            break;
        case 18:
            snake.speed = 120;
            break;
        case 21:
            snake.speed = 100;
            break;
        case 24:
            snake.speed = 80;
            break;
        case 27:
            snake.speed = 60;
            break;
        case 30:
            snake.speed = 40;
            break;
        default:
            break;
    }
}