#include <ncurses.h>
#include "display.h"
#include "snake.h"
#include "linked_list.h"
#include "world.h"
//All Color attributes are specified in main.c

//This function needs to be called in Snake.c 
void update_snake(Snake *snake) {
    attron(COLOR_PAIR(1));
    mvaddch(snake->list->head->y, snake->list->head->x, 'X');
    attroff(COLOR_PAIR(1));
}

//This function needs to be called in Snake.c when the player successfully eats food
void update_tail(Snake *snake) {
    attron(COLOR_PAIR(2));
    mvaddch(snake->list->tail->y, snake->list->tail->x, '*');
    attroff(COLOR_PAIR(2));
}

void add_food(World *world, int row, int column) {
    attron(COLOR_PAIR(3));
    mvaddch(row, column, '$');
    attron(COLOR_PAIR(3));
}

//Initialize starting world graphics
void add_initial_tiles(World *world) {
    for (int i = 0; i < world->rows; i ++) {
        for (int j = 0; j < world->columns; j ++) {
            if (world->tiles[i][j] == 1 || world->tiles[i][j] == 2) {
                mvaddch(i,j,'Y');
            }
        }
    }
}
