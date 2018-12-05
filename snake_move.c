#include <stdio.h>
#include <time.h>
#include <stdlib.h> 
#include <conio.h>

#define head 'H'
#define body 'X'
#define blank_char ' '
struct SNAKE 
{
    int x[100];
    int y[100];
    int lenth ;
}snake;
int gamerun = 1; 
char ch;

char map[10][11] = 
{
    "**********",
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "*        *",
    "**********" };
void PrintMap ()

{
    int i=0;
    system("cls");
    for ( i=0; i<10; i++ ) {
        printf("%s\n", map[i]);
    }
}

void GameOver () 
{
    gamerun = 0;
    printf("GAME OVER!\n");
} 

void InitGame() 
{
    snake.y[0] = snake.y[1] = snake.y[2] = snake.y[3] = 1;
    snake.x[0] = 5;
    snake.x[1] = 4;
    snake.x[2] = 3;
    snake.x[3] = 2;
    snake.lenth = 4; 
    map[snake.y[0]][snake.x[0]] = head;
    map[snake.y[1]][snake.x[1]] = body;
    map[snake.y[2]][snake.x[2]] = body;
    map[snake.y[3]][snake.x[3]] = body;
    map[snake.y[4]][snake.x[4]] = body;
    gamerun = 1;
    PrintMap();
}

void MoveSnake ()
{
    int i = 0;
    ch = _getch();
    map[snake.y[snake.lenth-1]][snake.x[snake.lenth-1]] = blank_char;
    map[snake.y[0]][snake.x[0]] = body;
    for( i=snake.lenth-1; i; i-- )
    {
        snake.x[i] = snake.x[i-1];
        snake.y[i] = snake.y[i-1];
    }  
    switch(ch) 
    {
        case 'w': snake.y[0]--; break;
        case 'a': snake.x[0]--; break;
        case 's': snake.y[0]++; break;
        case 'd': snake.x[0]++; break;
    }
    if(map[snake.y[0]][snake.x[0]] != blank_char ) GameOver();
    else map[snake.y[0]][snake.x[0]] = head;
}
//map[snake.y[snake.lenth-1]][snake.x[snake.lenth-1]] = blank_char;
int main() 
{
    InitGame() ;
    while (gamerun) 
    {   
        MoveSnake();
        PrintMap();
    }
    return 0;
}
