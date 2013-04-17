#ifndef SNAKELIB_H
#define SNAKELIB_H

const short M=16, N=51, K=10, start_len=(M-2)*(N-2);
const char cell[K]=" ", snake_icon[K]="\342\227\217", food_icon[K]="\342\231\245", border_icon[K]="\342\226\222";

struct Symbol
{
    short x;
    short y;
};

void input(char array[M][N][K]);
void draw(char array[M][N][K]);
void clear();
void move(char array[M][N][K], Symbol *snake, short n);
void snake_in(char array[M][N][K], Symbol *snake, short n);
void item_in(char array[M][N][K], Symbol food);
int kbhit();
int getch();

#endif

