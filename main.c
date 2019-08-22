#include <ncurses.h>
#include "snake.h"
#include "score.h"
#include "world.h"
#include "display.h"
#include "file_tools.h"
#include <time.h>
#include <stdlib.h>
#include <string.h>

void ncurses_init();

int main(int argc, char *argv[]) {
    ncurses_init();
    World *world = create_world(25,25);
    Score score;
    int file_status;
    file_status = read_from_file("highscores.bin",&score);
    if(file_status) {
        score.num_records = 0;
    }
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
                add_score(&score, "Ryan", world->snake->times_eaten);
                reset_world(world);
                display_new_screen(world,score);
            }
            update_snake(world->snake);
            refresh(); 
            start = clock();
            elapsed_time = 0;
        }
    }
    for (int i = 0; i < score.num_records; i ++) {
        printf("%s %d\n", score.names[i], score.scores[i]);
    }
    write_to_file("highscores.bin", score);
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
