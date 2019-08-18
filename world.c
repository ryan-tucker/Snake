#include "linked_list.h"
#include "snake.h"
#include "world.h"
#include "display.h"

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

World *create_world(int rows, int columns) {
    World *world = malloc(sizeof(World));
    world->rows = rows;
    world->columns = columns;
    world->tiles = create_tiles(rows, columns); 
    world->snake = create_snake(rows / 2, columns / 2);
    world->tiles[world->snake->list->head->y][world->snake->list->head->x] = SNAKE_ID;
    return world;
}

void delete_world(World *world) {
    delete_tiles(&world->tiles, world->rows,world->columns);
    delete_snake(world->snake);
    free(world);
}

void reset_world(World *world) {
    delete_tiles(&(world->tiles), world->rows, world->columns);
    world->tiles = create_tiles(world->rows, world->columns);
    delete_snake(world->snake);
    world->snake = create_snake(world->rows / 2, world->columns / 2);
    world->tiles[world->snake->list->head->y][world->snake->list->head->x] = SNAKE_ID;
    create_food(world);
    add_initial_tiles(world);
}

//Places food in a random index in world that is not currently occupied by the snake.
void create_food(World *world) {
    int rows = world->rows;
    int columns = world->columns;
    int **tiles = world->tiles;
    int rand_row, rand_column;
    do {
        rand_row = rand() % rows;
        rand_column = rand() % columns;
    } while (tiles[rand_row][rand_column] == 1);
    tiles[rand_row][rand_column] = 2;
    add_food(world, rand_row, rand_column);
}


int **create_tiles(int rows, int columns) {
    int **arr = malloc(sizeof(*arr) * rows);

    for (int i = 0; i < rows; i ++) {
        arr[i] = malloc(sizeof(int) * columns);
    }

    for (int i =0; i < rows; i ++) {
        for (int j = 0; j < columns; j ++) {
            arr[i][j] = 0;
        }
    }
    return arr;
}

void delete_tiles(int ***tiles, int rows, int columns) {
    int **arr = *tiles;
    for (int i = 0; i < rows; i ++) {
        free(arr[i]);
    }
    free(arr);
}
