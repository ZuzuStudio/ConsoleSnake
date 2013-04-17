#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "Snakelib.h"

using namespace std;

int main()
{
    srand(time(NULL));
    Symbol food, *snake=NULL;
    snake=new Symbol[start_len];
    short len=3;
    char field[M][N][K];
    input(field);
    snake_in(field, snake, len);
    do
    {
        food.x=rand()%(M-2)+1;
        food.y=rand()%(N-2)+1;
    }
    while (field[food.x][food.y][0]==snake_icon[0]);
    for (short k=0; k<K; ++k)
    field[food.x][food.y][k]=food_icon[k];

    draw(field);
    char button='d', twin=button;
    bool game=true;
    short score=0;
    while(game)
    {
        if(kbhit())
            button=getch();
        move(field, snake, len);
        if ((button=='s'&&twin!='w')||(button=='w'&&twin!='s')||(button=='a'&&twin!='d')||(button=='d'&&twin!='a'))
            twin=button;
        switch (twin)
        {
        case 'w':
            usleep(125000);
            snake[len-1].x--;
            if (snake[len-1].x<1)
                snake[len-1].x=M-2;
            break;
        case 's':
            usleep(125000);
            snake[len-1].x++;
            if (snake[len-1].x>M-2)
                snake[len-1].x=1;
            break;
        case 'a':
            usleep(100000);
            snake[len-1].y--;
            if (snake[len-1].y<1)
                snake[len-1].y=N-2;
            break;
        case 'd':
            usleep(100000);
            snake[len-1].y++;
            if (snake[len-1].y>N-2)
                snake[len-1].y=1;
            break;
        }
        if (field[snake[len-1].x][snake[len-1].y]==snake_icon)
        {
            game=false;
            cout<<endl<<"Счёт: "<<score<<endl;
            delete[]snake;
            sleep(1);
            continue;
        }

        for (short k=0; k<K; ++k)
        field[snake[len-1].x][snake[len-1].y][k]=snake_icon[k];
        clear();
        draw(field);
        if (field[snake[len-1].x][snake[len-1].y]==field[food.x][food.y])
        {
            len++;
            score++;
            snake[len-1].x=snake[len-2].x;
            snake[len-1].y=snake[len-2].y;

            do
            {
                food.x=rand()%(M-2)+1;
                food.y=rand()%(N-2)+1;
            }
            while (field[food.x][food.y][0]==snake_icon[0]);
            for (short k=0; k<K; ++k)
            field[food.x][food.y][k]=food_icon[k];
        }
    }
    return 0;
}
