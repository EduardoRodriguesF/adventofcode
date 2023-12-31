#ifndef ADVENT_14_GRID_H
#define ADVENT_14_GRID_H

#define ROLLING 'O'
#define CUBE '#'
#define EMPTY '.'

#include <stdlib.h>

typedef struct point {
    size_t x, y;
} Point;

typedef struct grid {
    char** rows;
    Point size;
} Grid;

char grid_at(const Grid* grid, Point point);
void grid_set(Grid* grid, Point point, char c);
void grid_move(Grid* grid, Point from, Point to);
void grid_inline(Grid* grid, char* buffer);

size_t grid_north_load(const Grid* grid);

void grid_tilt_north(Grid* grid);
void grid_tilt_west(Grid* grid);
void grid_tilt_south(Grid* grid);
void grid_tilt_east(Grid* grid);

void grid_draw(Grid* grid);

#endif
