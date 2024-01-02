#include "mirror.h"
#include <stdio.h>
#include <stdlib.h>

bool tile_has_passed(Tile* tile, Direction dir) {
    if ((tile->passed_dir_bits >> dir & 1) == 1) return true;

    tile->passed_dir_bits |= 1 << dir;

    return false;
}

Point point_sum(Point a, Point b) {
    return (Point){a.x + b.x, a.y + b.y};
}

Point point_vector(Direction dir) {
    Point vector = {0,0};
    switch (dir) {
        case Up:
            vector.y = -1;
            break;
        case Right:
            vector.x = 1;
            break;
        case Down:
            vector.y = 1;
            break;
        case Left:
            vector.x = -1;
            break;
    }

    return vector;
}

Grid* new_grid(size_t w, size_t h) {
    Grid* grid = malloc(sizeof(Grid) + (sizeof(Tile*) * w * h));
    grid->w = w;
    grid->h = h;

    for (int y = 0; y < grid->h; y++) {
        grid->rows[y] = malloc(sizeof(Tile*) * grid->w);
    }

    return grid;
}

Tile* grid_at(Grid* grid, int x, int y) {
    if (x < 0 || x >= grid->w || y < 0 || y >= grid->h) return NULL;

    return &grid->rows[y][x];
}

void grid_set(Grid* grid, int x, int y, char tile) {
    if (x < 0 || x > grid->w || y < 0 || y > grid->h) return;

    Tile entry;
    entry.data = tile;
    entry.energized = false;
    entry.passed_dir_bits = 0;

    grid->rows[y][x] = entry;
}

void reflect(Grid* grid, Point p, Direction dir) {
    Tile* tile;
    Point vector = point_vector(dir);

    for (p = point_sum(p, vector); (tile = grid_at(grid, p.x, p.y)) != NULL; p = point_sum(p, vector)) {
        tile->energized = true;
        if (tile->data == '.') continue;

        if (tile_has_passed(tile, dir)) return;

        if (tile->data == '\\' || tile->data == '/') {
            dir = hit_mirror(dir, tile->data);
            vector = point_vector(dir);
            continue;
        }

        if (tile->data == '|') {
            if (dir == Up || dir == Down) continue;

            reflect(grid, p, Up);

            dir = Down;
            vector = point_vector(dir);
            continue;
        }

        if (tile->data == '-') {
            if (dir == Right || dir == Left) continue;

            reflect(grid, p, Left);

            dir = Right;
            vector = point_vector(dir);
            continue;
        }
    }
}

Direction hit_mirror(Direction dir, char mirror) {
    if (mirror != '\\' && mirror != '/') {
        fprintf(stderr, "Invalid mirror: %c\n", mirror);
        exit(1);
    }

    switch (dir) {
        case Up:
            return mirror == '/' ? Right : Left;
        case Right:
            return mirror == '/' ? Up : Down;
        case Down:
            return mirror == '/' ? Left : Right;
        case Left:
            return mirror == '/' ? Down : Up;
    }
}
