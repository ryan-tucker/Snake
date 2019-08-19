#include <ncurses.h>
#include "snake.h"
#include "world.h"
#include "display.h"
#include "file_tools.h"
#include <time.h>
#include <stdlib.h>

void ncurses_init();

int main(int argc, char *argv[]) {
    ncurses_init();
    World *world = create_world(25,25);
    Score score;
    read_from_file("highscores.bin",&score);
    score.num_records = 5;
    char input = 0;
    clock_t start = clock();
    clock_t end_time = clock();
    double elapsed_time = 0;
    create_food(world);
    display_new_screen(world, score);
    refresh();
    while(input != 'q') { 
       input = getch();
       change_direction(world->snake, input);
       end_time = clock();
       elapsed_time += (end_time - start); 
       if (elapsed_time > 1000000000) { //Nasty trial and error number. Only tested on one machine.
            if (move_snake(world)) {
                display_new_screen(world,score);
            }
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

void ncurses_init() {
    initscr();
    nodelay(stdscr, true);
    raw();
    noecho();
    cbreak();
    curs_set(0);
    int row, column;
    getmaxyx(stdscr, row, column);

    start_color();
    init_colors();
}
