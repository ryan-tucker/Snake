#include <ncurses.h>
#include "snake.h"
#include "world.h"
#include "display.h"
#include <time.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    initscr();
    nodelay(stdscr, true);
    raw();
    noecho();
    cbreak();
    curs_set(0);
    int row, column;
    getmaxyx(stdscr, row, column);

    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    
    World *world = create_world(25,25);
    char input = 0;
    clock_t start = clock();
    clock_t end_time = clock();
    double elapsed_time = 0;
    for (int i = 0; i < world->rows; i ++) {
        for (int j = 0; j < world->columns; j ++) {
            if(world->tiles[i][j]==1) {
                attron(COLOR_PAIR(1));
               mvaddch(i,j,'X');
               attroff(COLOR_PAIR(1));
            } else {
                attron(COLOR_PAIR(2));
                mvaddch(i,j,'*');
                attroff(COLOR_PAIR(2));
            }
        }
    }
    create_food(world);
    while(input != 'q') { 
       input = getch();
       change_direction(world->snake, input);
       end_time = clock();
       elapsed_time += (end_time - start); 
       if (elapsed_time > 1000000000) {
            move_snake(world);
            update_snake(world->snake);
            refresh(); 
            start = clock();
            elapsed_time = 0;
        }
    }
    delete_world(world); 
    endwin();
    return 0;
}

