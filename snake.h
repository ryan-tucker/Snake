#ifndef SNAKE
#define SNAKE
#include "world.h"
#define UP 'w'
#define DOWN 's'
#define LEFT 'a'
#define RIGHT 'd'

typedef struct Snake {
    struct List *list;
    struct Coord *direction; // -1 <= x <= 1, -1 <= y <= 1
    int times_eaten;
} Snake;

Snake *create_snake(int x, int y);

void delete_snake(Snake *snake);

void change_direction(Snake *player, char input);

void move_snake(World *world);

#endif

