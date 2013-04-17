#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "Snakelib.h"

using namespace std;


void input(char array[M][N][K])
{
    for (short i=0; i<M; ++i)
        for (short j=0; j<N; ++j)
            for (short k=0; k<K; ++k)
            if (i==0||i==M-1||j==0||j==N-1)
                array[i][j][k]=border_icon[k];
            else
                array[i][j][k]=cell[k];
}

void draw(char array[M][N][K])
{
    for (short i=0; i<M; ++i)
    {
        for (short j=0; j<N; ++j)
            for (short k=0; k<K; ++k)
            cout<<array[i][j][k];
        cout<<endl;
    }
}

void clear()
{
    system ("clear");
}


void move(char array[M][N][K], Symbol *snake, short n)
{
    for (short k=0; k<K; ++k)
    array[snake[0].x][snake[0].y][k]=cell[k];
    for (short i=0; i<n-1; ++i)
    {
        snake[i].x=snake[i+1].x;
        snake[i].y=snake[i+1].y;
    }
}


void snake_in(char array[M][N][K], Symbol *snake, short n)
{
    for (short i=0; i<n; ++i)
    {
        snake[i].x=1;
        snake[i].y=i+1;
        for (short k=0; k<K; ++k)
        array[snake[i].x][snake[i].y][k]=snake_icon[k];
    }
}

void item_in(char array[M][N][K], Symbol food)
{
    do
    {
        food.x=rand()%(M-2)+1;
        food.y=rand()%(N-2)+1;
    }
    while (array[food.x][food.y][0]==snake_icon[0]&&array[food.x][food.y][1]==snake_icon[1]
                   &&array[food.x][food.y][2]==snake_icon[2]);
    for (short k=0; k<K; ++k)
    array[food.x][food.y][k]=food_icon[k];
}

int kbhit()
{
    struct termios oldt, newt;
    int ch;
    int oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if(ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

int getch()
{
    struct termios oldt, newt;
    int ch;
    tcgetattr( STDIN_FILENO, &oldt );
    newt = oldt;
    newt.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newt );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
    return ch;
}
