#include "linked_list.h"
#include "snake.h"
#include <stdio.h> 
#include <stdlib.h>
#include "coordinate.h"
#include "display.h"

Snake *create_snake(int x, int y) {
    Snake *snake = malloc(sizeof(Snake));    
    snake->list = create_list(); 
    snake->direction = malloc(sizeof(Coord));
    snake->direction->x = 1;
    snake->direction->y = 0;
    snake->times_eaten = 0;
    push(snake->list, x, y);
    return snake;
}

void delete_snake(Snake *snake) {
    delete_list(snake->list);
    free(snake->direction);
    free(snake);
}

void change_direction(Snake *player, char input) {
    int x_dir = player->direction->x;
    int y_dir = player->direction->y;

    switch (input) {
        case UP:
            if (y_dir == 0) {
                player->direction->y = -1;
                player->direction->x = 0;
            }
            break;
        case DOWN:
            if (y_dir == 0) {
                player->direction->y = 1;
                player->direction->x = 0;
            }
            break;
        case LEFT:
            if (x_dir == 0) {
                player->direction->x = -1;
                player->direction->y = 0;
            }
            break;
        case RIGHT:
            if (x_dir == 0) {
                player->direction->x = 1;
                player->direction->y = 0;
            }
            break;
    }
}
/*This function is not called on user input, it is called whenever a certain time threshold in main has been passed */
void move_snake(World *world) {
    int x_dir = world->snake->direction->x;
    int y_dir = world->snake->direction->y;
    int x_pos = world->snake->list->head->x;
    int y_pos = world->snake->list->head->y;
    int new_x_pos = x_pos + x_dir;
    int new_y_pos = y_pos + y_dir;
    int rows = world->rows;
    int columns = world->columns;
    
    //Bounds checking and collision with self
    if (new_x_pos < columns && new_x_pos >= 0 && new_y_pos < rows && new_y_pos >= 0 && world->tiles[new_y_pos][new_x_pos] != SNAKE_ID ) {
        push(world->snake->list, new_x_pos, new_y_pos);
        if (world->tiles[new_y_pos][new_x_pos] != FOOD_ID) {
            update_tail(world->snake); //Graphical update in logic :(
            world->tiles[world->snake->list->tail->y][world->snake->list->tail->x] = BACKGROUND_ID;
            delete_tail(world->snake->list); //New position does not contain food, therefore delete tail
        } else { //New position contains food, don't delete tail, create new food
            create_food(world);
            world->snake->times_eaten++;
        }
        world->tiles[new_y_pos][new_x_pos] = SNAKE_ID;
    } else {
        //do stuff with high score
        reset_world(world);
    }
}
