#ifndef ADVENT_16_MIRROR_H
#define ADVENT_16_MIRROR_H

#include <stdbool.h>
#include <stdlib.h>

typedef struct tile_t {
    char data;
    bool energized;
    short passed_dir_bits;
} Tile;

typedef struct grid_t {
    size_t w, h;
    Tile* rows[];
} Grid;

typedef struct point_t {
    int x, y;
} Point;

typedef enum direction {
    Up,
    Right,
    Down,
    Left,
} Direction;

Point point_sum(Point a, Point b);

Grid* new_grid(size_t w, size_t h);
Tile* grid_at(Grid* grid, int x, int y);
void grid_set(Grid* grid, int x, int y, char tile);
Direction hit_mirror(Direction dir, char mirror);

void reflect(Grid* grid, Point p, Direction dir);

#endif
