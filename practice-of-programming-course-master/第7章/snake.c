#include "snake.h"

/*全局变量定义*/
Snake snake;    //定义蛇结构体变量
Food food;        //定义食物结构体变量
char now_Dir = RIGHT;    //当前蛇头方向
char direction = RIGHT; //预期蛇头方向

/*主菜单实现*/
int Menu() {
    GotoXY(40, 12);                 //定位光标位置
    printf("欢迎来到贪吃蛇小游戏");
    GotoXY(43, 14);
    printf("1.开始游戏");
    GotoXY(43, 16);
    printf("2.帮助");
    GotoXY(43, 18);
    printf("3.关于");
    GotoXY(43, 20);
    printf("其他任意键退出游戏");
    Hide();                           //隐藏光标
    char ch;
    int result = 0;
    ch = _getch();                //接收用户输入的菜单选项
    switch (ch) {                //根据选项设置返回结果值
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
    system("cls");                //调用系统命令cls完成清屏操作
    return result;
}

//qsort函数实现
int comp(const void *a, const void *b) {
    return *(int *) b - *(int *) a;
}

//光标定位函数，将光标定位到(x,y)坐标位置
void GotoXY(int x, int y) {
    HANDLE hout;
    COORD cor;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    cor.X = x;
    cor.Y = y;
    SetConsoleCursorPosition(hout, cor);
}

/*隐藏光标*/
void Hide() {
    HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cor_info = {1, 0};
    SetConsoleCursorInfo(hout, &cor_info);
}


/*关于菜单实现*/
void About() {
    GotoXY(30, 12);
    printf("杭州电子科技大学--程序设计综合实践案例");
    GotoXY(43, 14);
    printf("贪吃蛇-控制台游戏");
    GotoXY(43, 16);
    printf("按任意键返回上级菜单");
    Hide();        //隐藏光标
    char ch = _getch();
    system("cls");
}

/*帮助菜单实现*/
void Help() {
    GotoXY(40, 12);
    printf("w 上");
    GotoXY(40, 14);
    printf("s 下");
    GotoXY(40, 16);
    printf("a 左");
    GotoXY(40, 18);
    printf("d 右");
    GotoXY(40, 20);
    printf("当蛇撞到自身或撞墙时游戏结束");
    GotoXY(45, 22);
    printf("按任意键返回上级菜单");
    Hide();        //隐藏光标
    char ch = _getch();
    system("cls");
}

/*初始化地图函数*/
void InitMap() {
    Hide();                    //隐藏光标
    //设置蛇头位置在地图中心
    snake.snakeNode[0].x = MAP_WIDTH / 2 - 1;
    snake.snakeNode[0].y = MAP_HEIGHT / 2 - 1;
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);      //将光标移动到蛇头位置
    printf("@");                //打印蛇头
    snake.length = 3;        //设置蛇长初始值为3节
    snake.speed = 250;        //设置蛇初始移动速度为250
    now_Dir = RIGHT;            //当前蛇头方向
    //显示蛇身
    for (int i = 1; i < snake.length; i++) {
        //设置蛇身的纵坐标位置和蛇头位置相同
        snake.snakeNode[i].y = snake.snakeNode[i - 1].y;
        //设置蛇身的横坐标位置，蛇身在蛇头的左边,所以横坐标依次减1
        snake.snakeNode[i].x = snake.snakeNode[i - 1].x - 1;
        GotoXY(snake.snakeNode[i].x, snake.snakeNode[i].y);    //移动光标到蛇身位置
        printf("0");        //打印蛇身
    }
    //生成地图上下边界
    for (int i = 0; i < MAP_WIDTH; i++) {
        GotoXY(i, 0);
        printf("─");
        GotoXY(i, MAP_HEIGHT - 1);
        printf("─");
    }
    for (int i = 1; i < MAP_HEIGHT - 1; i++) {
        GotoXY(0, i);
        printf("┃");
        GotoXY(MAP_WIDTH - 1, i);
        printf("┃");
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


    //生成食物
    PrintFood();
    //得分说明
    qsort(Leaderboard, 10, sizeof(int), comp);
    GotoXY(105, 0);
    printf("当前得分:0");
    GotoXY(105, 2);
    printf("积分排行榜");
    //生成排行榜上下边界
    for (int i = 0; i < LIST_WIDTH; i++) {
        GotoXY(101 + i, 3);
        printf("─");
        GotoXY(101 + i, 2 + LIST_HEIGHT);
        printf("─");
    }
    //生成排行榜左右边界
    for (int i = 1; i < LIST_HEIGHT - 1; i++) {
        GotoXY(100, 3 + i);
        printf("┃");
        GotoXY(101 + LIST_WIDTH, 3 + i);
        printf("┃");
    }
    int temp = 0;
    for (int i = 0; i < sizeof(Leaderboard) / sizeof(Leaderboard[0]); ++i) {
        temp = temp + 2;
        GotoXY(101, 4 + temp);
        printf("  NO.%d : %d 分", i + 1, Leaderboard[i]);
    }
}

/*生成食物函数*/
void PrintFood() {
    int flag = 1;
    while (flag) {
        flag = 0;
        //设置随机的食物坐标位置
        food.x = rand() % (MAP_WIDTH - 2) + 1;
        food.y = rand() % (MAP_HEIGHT - 2) + 1;
        //循环判断食物位置是否和蛇的位置重叠，如果重叠则需要重新设置食物位置
        for (int k = 0; k <= snake.length - 1; k++) {
            if (snake.snakeNode[k].x == food.x && snake.snakeNode[k].y == food.y) {
                flag = 1;                //位置有重叠，需要继续循环
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


/*蛇移动函数实现,返回值为1表示继续移动，为0表示停止移动*/
int MoveSnake() {
    Snakenode temp;
    int flag = 0;
    temp = snake.snakeNode[snake.length - 1];            //记录蛇尾
    for (int i = snake.length - 1; i >= 1; i--)
        snake.snakeNode[i] = snake.snakeNode[i - 1];    //将所有蛇身向前移动一个位置
    GotoXY(snake.snakeNode[1].x, snake.snakeNode[1].y);
    printf("0");            //前进方向打印一节蛇身，其他蛇身不需要打印
    //响应键盘修改
    if (_kbhit()) {            //键盘输入返回1，非键盘输入返回0
        direction = _getch();
        switch (direction) {
            case UP:  //按下w键
                if (now_Dir != DOWN)        //如果蛇头向下，按向上移动的键w时不起作用
                    now_Dir = direction;
                break;
            case DOWN:  //按下s键
                if (now_Dir != UP)            //如果蛇头向上，按向下移动的键s时不起作用
                    now_Dir = direction;
                break;
            case LEFT:  //按下a键
                if (now_Dir != RIGHT)        //如果蛇头向右，按向左移动的键a时不起作用
                    now_Dir = direction;
                break;
            case RIGHT:  //按下d键
                if (now_Dir != LEFT)        //如果蛇头向左，按向右移动的键d时不起作用
                    now_Dir = direction;
                break;
        }
    }
    switch (now_Dir) {                    //根据现在的方向修改蛇头的位置
        case UP:
            snake.snakeNode[0].y--;
            break;        //向上移动
        case DOWN:
            snake.snakeNode[0].y++;
            break;        //向下移动
        case LEFT:
            snake.snakeNode[0].x--;
            break;        //向左移动
        case RIGHT:
            snake.snakeNode[0].x++;
            break;    //向右移动
    }
    //打印蛇头
    GotoXY(snake.snakeNode[0].x, snake.snakeNode[0].y);
    printf("@");
    //判断是否吃到食物，如果蛇头的位置和食物的位置相同表示吃到食物
    if (snake.snakeNode[0].x == food.x && snake.snakeNode[0].y == food.y) {
        flag = 1;            //flag为1表示吃到食物，为0表示没有吃到食物
        if (FoodCategory == '#') {
            snake.length++;//吃到食物，蛇长加1
            snake.snakeNode[snake.length - 1] = temp;    //吃到食物，蛇尾加一节
        }
        if (FoodCategory == '$') {
            /*
             * 吃到'$'蛇尾加两节
             * */
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
            snake.length++;
            snake.snakeNode[snake.length - 1] = temp;
        }
        if (FoodCategory == '&') {
            /*
             * 吃到'&'蛇尾加三节
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
             * 吃到'*'蛇尾加四节
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
    //输出蛇此时状态
    //没吃到食物时，在原来的蛇尾打印一个空格，去掉原来的蛇尾
    if (!flag) {
        GotoXY(temp.x, temp.y);
        printf(" ");
    } else {            //吃到食物，则需要在地图上重新更新一个食物
        PrintFood();
        GotoXY(105, 0);
        printf("当前得分:%d", snake.length - 3);    //打印得分，得分为蛇长减原始长度3
    }
    //判断是否死亡
    if (!IsCorrect()) {        //如果自撞或撞墙，则清楚屏幕，打印最终得分，游戏结束
        system("cls");
        GotoXY(45, 14);
        printf("最终得分：%d", snake.length - 3);
        Leaderboard[Leaderboard_count++] = snake.length - 3;
        GotoXY(45, 16);
        printf("你输了！");
        GotoXY(45, 18);
        printf("按任意键返回主菜单");
        char c = _getch();
        system("cls");
        return 0;
    }
    //调整速度
    SpeedControl();
    Sleep(snake.speed);        //把进程挂起一段时间，用于控制蛇移动的速度
    return 1;
}

/*判断是否自撞或撞墙,返回值为0表示自撞或撞墙，否则为1*/
int IsCorrect() {
    if (snake.snakeNode[0].x == 0 || snake.snakeNode[0].y == 0 || snake.snakeNode[0].x == MAP_WIDTH - 1 ||
        snake.snakeNode[0].y == MAP_HEIGHT - 1) //判断蛇头是否撞墙
        return 0;
    if ((snake.snakeNode[0].x == 30 && 10 <= snake.snakeNode[0].y && snake.snakeNode[0].y <= 20) ||
        (snake.snakeNode[0].x == 70 && 10 <= snake.snakeNode[0].y && snake.snakeNode[0].y <= 20) ||
        (snake.snakeNode[0].y == 20 && 30 <= snake.snakeNode[0].x && snake.snakeNode[0].x <= 50) ||
        (snake.snakeNode[0].y == 10 && 50 <= snake.snakeNode[0].x && snake.snakeNode[0].x <= 70))
        return 0;
    for (int i = 1; i < snake.length; i++) {   //判断蛇头是否和蛇身重叠，重叠表示自撞
        if (snake.snakeNode[0].x == snake.snakeNode[i].x && snake.snakeNode[0].y == snake.snakeNode[i].y) {
            GotoXY(snake.snakeNode[snake.length - 1].x, snake.snakeNode[snake.length - 1].y);
            printf(" ");
            snake.length--;
            GotoXY(105, 0);
            printf("当前得分:%d", snake.length - 3);
        }
    }
    return 1;
}

/*速度调整函数*/
void SpeedControl() {
    switch (snake.length) {        //根据蛇长调整蛇的移动速度
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