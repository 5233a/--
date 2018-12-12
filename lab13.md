# 贪吃蛇代码学习
## 背景
在学完自顶向下的编程方法后，余阳老师让我们自己编写贪食蛇的代码。说心里话，我的内心是崩溃的，作为一个计算机小白，别说贪食蛇，就连有些基础的编程题都能
让我写不出来。突然出现这么难的题目，该如何是好呢？于是乎，我仔细的阅读了作业要求上的讲解，才知道了，我们要做的事，并不是直接就要写出如此高大上的代码，
而是通过这个过程，领略到编程的魅力。那之后，我在CSDN上找到了关于贪食蛇和智能蛇的代码，仔细研读一番之后，虽说对大部分内容仍一知半解，但是也多少理解了
这串代码的意义，现在，我就通过这个过程讲述一下我的心得体会吧。
## 代码（来源于CSDN）
```
/*蛇越长跑得越快*/
/*蛇能自己找食物*/
/*作者：SGAFPZ*/
#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <math.h>
//#include <unistd.h>
#include <conio.h>
#include <string.h>
#include <time.h>
void food();
void show();
void move();
void turn();
void check();
void ini();
void calculate();
int movable[4] = { 0, 1, 1, 0 };  //数组的下标表示方向，0123分别表示上下左右，下同
int distance[4] = { 9999, 9999, 9999, 9999 };
int  dy[4] = { 0, 1, 0, -1 };
int  dx[4] = { -1, 0, 1, 0 };
int sum = 5;  //蛇总长度
int over = 0;
int speed;   
int foodx, foody;  //食物的坐标
char map[17][17];

struct snake {
    int x, y;  //身体坐标 
    int dir;  //方向（只有蛇头的方向是有用的） 
} A[100];

void ini() {  //初始化界面
    speed = 500;
    over = 0;
    sum = 5;
    movable[0] = 0; movable[1] = 1; movable[2] = 1; movable[3] = 0;
    distance[0] = 9999; distance[1] = 9999; distance[2] = 9999; distance[3] = 9999;
    int i, j;
    for (i = 0; i < 100; i++) {  //初始化蛇头和蛇身的数据
        A[i].dir = 0;
        A[i].x = 0;
        A[i].y = 0;
    }
    A[0].x = 1; A[0].y = 1;  //地图左上角设置一条长度为5的蛇
    A[1].x = 1; A[1].y = 2;
    A[2].x = 1; A[2].y = 3;
    A[3].x = 1; A[3].y = 4;
    A[4].x = 1; A[4].y = 5; A[4].dir = 1;
    srand(time(0));
    for (i = 0; i < 17; i++) {  //设置地图
        for (j = 0; j < 17; j++) {
            map[i][j] = '*';
        }
    }
    for (i = 1; i < 16; i++) {
        for (j = 1; j < 16; j++) {
            map[i][j] = ' ';
       }
    }
   //map[6][5] = '*'; map[6][6] = '*'; map[6][7] = '*';
    //map[7][5] = '*'; map[7][7] = '*';
    map[A[4].x][A[4].y] = 'H';  //设置蛇头
    for (i = 0; i < sum - 1; i++) {  //设置蛇身
        map[A[i].x][A[i].y] = 'X';
    }
    food();
    calculate();
}


void show() {  //显示界面 
    int i, j, x, y;
    for (i = 0; i < 17; i++) {  //显示界面
        for (j = 0; j < 17; j++) {
            printf("%c", map[i][j]);
        }
        printf("\n");
    }
    while (1) {
        Sleep(speed);  //界面刷新速度
        turn();
        move();
        if (over) {  //设置蛇死掉后可以进行的操作 
            while (1) {
                char ch = _getch();
                if (ch == 113) {  //输入‘q’结束 
                    return;
                }
                else if (ch == 114) {  //输入‘r’重新开始 
                    ini();
                    break;
                }
            }
        }
        system("cls");  //清屏 
        for (i = 0; i < 17; i++) {  //重新显示界面
            for (j = 0; j < 17; j++) {
                printf("%c", map[i][j]);
            }
            printf("\n");
        }
        calculate(); //计算并记录蛇头与食物距离
    }
}

void food() {  //生成食物
    int x, y;
    while (1) {
        x = (int)(15 * rand() / (RAND_MAX + 1.0));  //随机产生一组食物坐标
        y = (int)(15 * rand() / (RAND_MAX + 1.0));
        if (map[x][y] == ' ') {  //如果是空格则在该处生成食物
            map[x][y] = 'O';
            foodx = x;  //记录食物坐标 
            foody = y;
            break;
        }
    }
}


void move() {  //蛇移动
    int i, x, y;
    int t = sum;  //t记录当前蛇总长度 
    check();  //移动前检查按当前方向移动一步后的情况
    if (t == sum) {  //没有吃到苹果
        for (i = 0; i < sum - 1; i++) {
            if (i == 0) {  //蛇尾坐标处变成空格，把蛇尾坐标变成前一个蛇身的坐标 
                map[A[i].x][A[i].y] = ' ';
                A[i].x = A[i + 1].x;
                A[i].y = A[i + 1].y;
            }
            else {  //每个蛇身坐标都变为它前一个蛇身的坐标
                A[i].x = A[i + 1].x;
                A[i].y = A[i + 1].y;
            }
            map[A[i].x][A[i].y] = 'X';  //把地图上蛇身坐标处的字符设置成‘X’
        }
        A[sum - 1].x = A[sum - 1].x + dx[A[sum - 1].dir];  //蛇头按当前方向移动一格 
        A[sum - 1].y = A[sum - 1].y + dy[A[sum - 1].dir];
        map[A[sum - 1].x][A[sum - 1].y] = 'H';  //把地图上蛇头坐标处的字符设置成‘H’
    }
    else {  //吃到苹果（sum会加1）
        map[A[sum - 2].x][A[sum - 2].y] = 'X';  //把地图上原蛇头坐标处的字符设置成‘X’
        A[sum - 1].x = A[sum - 2].x + dx[A[sum - 2].dir];  //新蛇头的坐标是原蛇头沿当前方向移动一格后的坐标 
        A[sum - 1].y = A[sum - 2].y + dy[A[sum - 2].dir];
        A[sum - 1].dir = A[sum - 2].dir;  //新蛇头方向为原蛇头的方向
        map[A[sum - 1].x][A[sum - 1].y] = 'H';  //把地图上蛇头坐标处的字符设置成‘H’
        food();
    }
    for(i = 0; i < 4; i++) {  //记录下能走的方向
        x = A[sum - 1].x + dx[i];
        y = A[sum - 1].y + dy[i];
        if(map[x][y] == ' ' || map[x][y] == 'O') {
            movable[i] = 1;  //能走就把对应方向的值设置为1 
        } else {
            if(x != A[0].x || y != A[0].y) {
                movable[i] = 0;  //不能走就把对应方向的值设置为0 
            } else {
                movable[i] = 1;
            }
        }
    }
}

void check() {  //检查是否死亡或者吃到食物
    int x, y, i, j;
    x = A[sum - 1].x + dx[A[sum - 1].dir];  //记录按当前方向移动一格后蛇头的坐标 
    y = A[sum - 1].y + dy[A[sum - 1].dir];
    if (map[x][y] == '*' || map[x][y] == 'X') {  //如果地图上该坐标处字符为‘*’或‘X’就死亡 
        if (x != A[0].x || y != A[0].y) {  //蛇尾除外 
            map[8][4] = 'G'; map[8][5] = 'A'; map[8][6] = 'M'; map[8][7] = 'E';  //输出“GAME OVER” 
            map[8][9] = 'O'; map[8][10] = 'V'; map[8][11] = 'E'; map[8][12] = 'R';
            map[8][8] = ' ';
            system("cls");
            for (i = 0; i < 17; i++) {
                for (j = 0; j < 17; j++) {
                    printf("%c", map[i][j]);
                }
                printf("\n");
            }
            printf("Input 'r' to restart\nInput 'q' to quit\n");
            over = 1;
        }
    }
    else if (map[x][y] == 'O') {  //吃到苹果 
        sum++;  //蛇身总长加1 
        speed = ((600 - sum * 20)>100) ? (600 - sum * 20) : 100; //速度加快 
    }
}

void turn() {  //转弯
    int i, k = 0;
    for(i = 1; i < 4; i++) {  //找到走一步后离食物距离最短的方向
        if(distance[k] > distance[i]) {
            k = i;
        }
    }
    switch (k) {  //把把蛇头方向改为该方向 
        case 0: A[sum - 1].dir = (A[sum - 1].dir == 2)?2:0; break;
        case 1: A[sum - 1].dir = (A[sum - 1].dir == 3)?3:1; break;
        case 2: A[sum - 1].dir = (A[sum - 1].dir == 0)?0:2; break;
        case 3: A[sum - 1].dir = (A[sum - 1].dir == 1)?1:3; break;
    }
}

void calculate() {  //计算并记录蛇头与食物距离
    int i = 0, x, y;
    for(i = 0; i < 4; i++) {
        if(movable[i] == 1) {  //如果该方向能走，则记录下沿该方向走一步后与食物的距离 
            x = A[sum - 1].x + dx[i];
            y = A[sum - 1].y + dy[i];
            distance[i] = abs(foodx-x)+abs(foody-y);
        } else {  //如果不能走则把距离设置为9999 
            distance[i] = 9999;
        }
    }
}

int main() {
    printf("你只需要静静地看着它跑\n");
    printf("按任意键开始\n");
    char ch = _getch();
    system("cls");
    ini();
    show();
    return 0;
}
--------------------- 
作者：SGAFPZ 
来源：CSDN 
原文：https://blog.csdn.net/SGAFPZys/article/details/51180061 
版权声明：本文为博主原创文章，转载请附上博文链接！
```
## 学习心得
刚拿到这个题目脑中就是一片空白，随之而来的是一堆疑问奔涌而出，以至于不知道该从哪个问题开始思考。冷静下来之后我发现所有问题之中最致命的是如何让编译器连续输出每一帧以形成动画的感觉，对我来说这属于超出知识范畴的硬伤，所以我迫不及待的打开百度查找答案，但看了各种眼花缭乱的操作之后还是一头雾水。在发了许久的懵后猛然醒悟，遇到这种复杂的问题应该要有意识的按照“自顶向下，逐步求精”的基本法思考问题而不是想一出是一出。 

首先将程序目的大致分为几个步骤来实现：

显示背景图，蛇，食物
让蛇随着玩家键入的方向键移动
若蛇吃到食物则加长一节，若蛇碰到墙或自己则GAMEOVER。

在完成上述三个步骤的基本思后考再加入优化游戏体验的人性化设计，一个大致的框架就形成了。接下来只要按照这个框架逐步求精就OK了。

将每个功能都封装进函数让思路更清晰。

void begin(); 
//登陆界面，大概介绍一下游戏规则以及操作方法。

void setfoodcrd(); 
// 随机设置食物要出现的坐标，在相应的坐标画出食物（注意不与边框或蛇重合，当食物被吃掉后才能再生产）。

void setsnakecrd(); 
//初始蛇要出现的坐标，在相应的坐标画出蛇。

void show(); 
//显示出游戏画面。

void changeskdir(); 
//接受玩家键入的方向键并改变蛇的移动方向（注意蛇默认向前走，键入相反方向是不合法的）。

void snakemove(); 
// 移动蛇，实际就是改变蛇各节的坐标。

void judge(); 
//若蛇吃到食物蛇身加长；若蛇碰到自己或墙显示GAMEOVER。

将一个大问题分解成这样一个个的小问题后，用代码解决就是水到渠成的事情了。
