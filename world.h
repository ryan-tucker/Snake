#ifndef WORLD
#define WORLD
#define BACKGROUND_ID 0
#define SNAKE_ID 1
#define FOOD_ID 2

typedef struct World {
    int **tiles;
    int rows;
    int columns;
    struct Snake *snake; 
} World;

int **create_tiles(int rows, int columns);

void delete_tiles(int ***tiles, int rows, int columns);

World *create_world(int rows, int columns);

void create_food(World *world);

void delete_world(World *world);

void output_world(World *world);

void update_world(World *world);

#endif
