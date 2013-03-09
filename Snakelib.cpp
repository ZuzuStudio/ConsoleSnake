#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include "Snakelib.h"

using namespace std;

void init (char array[M][N], int M, int N)
{
   for (short i = 0; i < M; ++i)
      for (short j = 0; j < N; ++j)
         if (i == 0 || i == M - 1 || j == 0 || j == N - 1)
            array[i][j] = border_icon;
         else
            array[i][j] = cell;
}

void draw (char array[M][N], int M, int N)
{
   for (short i = 0; i < M; ++i)
   {
      for (short j = 0; j < N; ++j)
         cout << array[i][j];

      cout << endl;
   }
}

void clear()
{
   system ("clear");
}

void move (char array[M][N], int M, int N, Symbol *snake, short n)
{
   array[snake[0].x][snake[0].y] = cell;

   for (short i = 0; i < n - 1; ++i)
   {
      snake[i].x = snake[i+1].x;
      snake[i].y = snake[i+1].y;
   }
}

void snake_in (char array[M][N], int M, int N, Symbol *snake, short n)
{
   for (short i = 0; i < n; ++i)
   {
      snake[i].x = 1;
      snake[i].y = i + 1;
      array[snake[i].x][snake[i].y] = snake_icon;
   }
}

void item_in (char array[M][N], int M, int N, Symbol &food)
{
   do
   {
      food.x = rand() % (M - 2) + 1;
      food.y = rand() % (N - 2) + 1;
   }
   while (array[food.x][food.y] == snake_icon);

   array[food.x][food.y] = food_icon;
}

int kbhit()
{
   struct termios oldt, newt;
   int ch;
   int oldf;

   tcgetattr (STDIN_FILENO, &oldt);
   newt = oldt;
   newt.c_lflag &= ~ (ICANON | ECHO);
   tcsetattr (STDIN_FILENO, TCSANOW, &newt);
   oldf = fcntl (STDIN_FILENO, F_GETFL, 0);
   fcntl (STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

   ch = getchar();

   tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
   fcntl (STDIN_FILENO, F_SETFL, oldf);

   if (ch != EOF)
   {
      ungetc (ch, stdin);
      return 1;
   }

   return 0;
}

int getch()
{
   struct termios oldt, newt;
   int ch;
   tcgetattr (STDIN_FILENO, &oldt);
   newt = oldt;
   newt.c_lflag &= ~ (ICANON | ECHO);
   tcsetattr (STDIN_FILENO, TCSANOW, &newt);
   ch = getchar();
   tcsetattr (STDIN_FILENO, TCSANOW, &oldt);
   return ch;
}
