#include "mirror.h"
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    size_t bufsize = 128;
    char* line = malloc(bufsize);
    Grid* grid = NULL;

    int y = 0;
    while (getline(&line, &bufsize, stdin) > 0) {
        if (grid == NULL) {
            int n = 0;
            while (!isspace(line[n]) && line[n] != '\0') n++;
            grid = new_grid(n, n);
        };

        for (int x = 0; !isspace(line[x]) && line[x] != '\0'; x++) {
            grid_set(grid, x, y, line[x]);
        }

        y++;
    }

    size_t r = 0;
    Point p;
    for (p = (Point){-1,0}; p.y < grid->h; p.y++) {
        grid_reset(grid);
        reflect(grid, p, Right);
        size_t energy = grid_energy(grid);
        if (energy > r) r = energy;
    }

    for (p = (Point){-1,grid->w-1}; p.y < grid->h; p.y++) {
        grid_reset(grid);
        reflect(grid, p, Left);
        size_t energy = grid_energy(grid);
        if (energy > r) r = energy;
    }

    for (p = (Point){0,-1}; p.x < grid->w; p.x++) {
        grid_reset(grid);
        reflect(grid, p, Down);
        size_t energy = grid_energy(grid);
        if (energy > r) r = energy;
    }

    for (p = (Point){grid->w-1,-1}; p.x < grid->w; p.x++) {
        grid_reset(grid);
        reflect(grid, p, Up);
        size_t energy = grid_energy(grid);
        if (energy > r) r = energy;
    }

    printf("%zu\n", r);
}
