#include <ncurses.h>
#include "display.h"
#include "score.h"
#include "snake.h"
#include "linked_list.h"
#include "world.h"

void init_colors() {
    init_color(COLOR_GREEN, 0, 650, 0);
    init_color(COLOR_RED, 650, 0, 0);
    init_color(COLOR_BLUE, 0, 700, 700);
    init_pair(FOOD_COLOR_PAIR, COLOR_GREEN, COLOR_BLACK);
    init_pair(BACKGROUND_COLOR_PAIR, COLOR_RED, COLOR_BLACK);
    init_pair(SNAKE_COLOR_PAIR, COLOR_BLUE, COLOR_BLACK);
    init_pair(TEXT_COLOR_PAIR, COLOR_WHITE, COLOR_BLACK);
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
    attroff(COLOR_PAIR(FOOD_COLOR_PAIR));
}

void display_highscores(World *world, Score score) {
    int width = world->columns;
    int height = world->rows;

    int x = width + 5;
    int y = 0;
    attron(COLOR_PAIR(TEXT_COLOR_PAIR));
    mvprintw(y++,x, "High Scores");
    for (int i = 0; i < score.num_records; i ++) {
        mvprintw(y,x,"%s : %d", score.names[i], score.scores[i]);
        y += 1;
    }
    attroff(COLOR_PAIR(TEXT_COLOR_PAIR));
}

void display_current_score(World *world) {
    int score = world->snake->times_eaten;
    attron(COLOR_PAIR(TEXT_COLOR_PAIR));
    mvprintw(world->rows / 2,world->columns+1,"%d",score);
    attroff(COLOR_PAIR(TEXT_COLOR_PAIR));
}

//Initialize starting world graphics
void add_initial_tiles(World *world) {
    for (int i = 0; i < world->rows; i ++) {
        for (int j = 0; j < world->columns; j ++) {
            if(world->tiles[i][j]==SNAKE_ID) {
                attron(COLOR_PAIR(SNAKE_COLOR_PAIR));
                mvaddch(i,j,SNAKE_SYMBOL);
                attroff(COLOR_PAIR(SNAKE_COLOR_PAIR));
            } else if (world->tiles[i][j]==BACKGROUND_ID) {
                attron(COLOR_PAIR(BACKGROUND_COLOR_PAIR));
                mvaddch(i,j,BACKGROUND_SYMBOL);
                attroff(COLOR_PAIR(BACKGROUND_COLOR_PAIR));
            } else if (world->tiles[i][j]==FOOD_ID) {
                add_food(world,i,j);
            }
        }
    }
}

void display_new_screen(World *world, Score score) {
    clear();
    add_initial_tiles(world);
    display_highscores(world, score);
    display_current_score(world);
}
