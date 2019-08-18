#include <ncurses.h>
#include "display.h"
#include "snake.h"
#include "linked_list.h"
#include "world.h"

void init_colors() {
    init_pair(SNAKE_COLOR_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(BACKGROUND_COLOR_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(FOOD_COLOR_PAIR, COLOR_BLUE, COLOR_BLACK);
}
//This function needs to be called in Snake.c 
void update_snake(Snake *snake) {
    attron(COLOR_PAIR(SNAKE_COLOR_PAIR));
    mvaddch(snake->list->head->y, snake->list->head->x, SNAKE_SYMBOL);
    attroff(COLOR_PAIR(SNAKE_COLOR_PAIR));
}

//This function needs to be called in Snake.c when the player successfully eats food
void update_tail(Snake *snake) {
    attron(COLOR_PAIR(BACKGROUND_COLOR_PAIR));
    mvaddch(snake->list->tail->y, snake->list->tail->x, BACKGROUND_SYMBOL);
    attroff(COLOR_PAIR(BACKGROUND_COLOR_PAIR));
}

void add_food(World *world, int row, int column) {
    attron(COLOR_PAIR(FOOD_COLOR_PAIR));
    mvaddch(row, column, FOOD_SYMBOL);
    attron(COLOR_PAIR(FOOD_COLOR_PAIR));
}

//Initialize starting world graphics
void add_initial_tiles(World *world) {
    for (int i = 0; i < world->rows; i ++) {
        for (int j = 0; j < world->columns; j ++) {
            if(world->tiles[i][j]==1) {
                attron(COLOR_PAIR(SNAKE_COLOR_PAIR));
                mvaddch(i,j,SNAKE_SYMBOL);
                attroff(COLOR_PAIR(SNAKE_COLOR_PAIR));
            } else {
                attron(COLOR_PAIR(BACKGROUND_COLOR_PAIR));
                mvaddch(i,j,BACKGROUND_SYMBOL);
                attroff(COLOR_PAIR(BACKGROUND_COLOR_PAIR));
            }
        }
    }
}
