#ifndef DISPLAY_H
#define DISPLAY_H
#include "snake.h"
#include "world.h"
#include "score.h"

#define SNAKE_COLOR_PAIR 1
#define BACKGROUND_COLOR_PAIR 2
#define FOOD_COLOR_PAIR 3
#define SNAKE_SYMBOL 'X'
#define BACKGROUND_SYMBOL '*'
#define FOOD_SYMBOL '$'

void init_colors();
void display_new_screen(World *world, Score score);
void display_highscores(World *world, Score score); 
void display_current_score(World *world);
void update_snake(Snake *snake);
void update_tail(Snake *snake);
void add_food(World *world, int row, int column);
void add_initial_tiles(World *world);
#endif
