#ifndef SNAKELIB_H
#define SNAKELIB_H

const short M = 16, N = 51, start_len = (M - 2) * (N - 2);
const char cell = ' ', snake_icon = 'O', food_icon = '+', border_icon = '#';

struct Symbol
{
   short x;
   short y;
};

void init (char **array, int M, int N);
void draw (char **array, int M, int N);
void clear();
void move (char **array, int M, int N, Symbol *snake, short n);
void snake_in (char **array, int M, int N, Symbol *snake, short n);
void item_in (char **array, int M, int N, Symbol &food);
int kbhit();
int getch();

#endif


