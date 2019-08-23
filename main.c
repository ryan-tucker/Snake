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
void get_user_name(World world, char buffer[MAX_NAME_LENGTH]);

int main(int argc, char *argv[]) {
    int file_status;
    char input = 0;
    clock_t start, end_time;
    double elapsed_time = 0;
    char name[MAX_NAME_LENGTH];
    ncurses_init();
    World *world = create_world(25,25);
    Score score;
    file_status = read_from_file("highscores.bin",&score);
    if(file_status) {
        score.num_records = 0;
    }
    create_food(world);
    display_new_screen(world, score);
    start = end_time = clock();
    refresh();
    while(input != 'q') { 
       input = getch(); 
       change_direction(world->snake, input);
       end_time = clock();
       elapsed_time += (end_time - start); 
       if (elapsed_time > 1000000000) { //Nasty trial and error number. Only tested on one machine.
            if (move_snake(world)) {
                if (check_score(score, world->snake->times_eaten)) {
                    get_user_name(*world, name);
                    add_score(&score, name, world->snake->times_eaten);
                }
                reset_world(world);
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
    start_color();
    init_colors();
}

void get_user_name(World world,char buffer[MAX_NAME_LENGTH]) {
    static char *prompt = "Please Enter Your Name:";
    nodelay(stdscr, false);
    echo();
    curs_set(1);
    attron(COLOR_PAIR(TEXT_COLOR_PAIR));
    mvprintw(world.rows / 2 + 1, world.columns + 1,"%s", prompt);
    move(world.rows / 2 + 2, world.columns + 1);
    getstr(buffer);
    nodelay(stdscr, true);
    noecho();
    curs_set(0);
    attroff(COLOR_PAIR(TEXT_COLOR_PAIR));
}
