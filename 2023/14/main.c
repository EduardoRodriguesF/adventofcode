#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"
#include "hashmap.h"

#define GRID_AREA (128 * 128)
#define CYCLES 1000000000

void cycle(Grid* grid) {
    grid_tilt_north(grid);
    grid_tilt_west(grid);
    grid_tilt_south(grid);
    grid_tilt_east(grid);
}

int main() {
    size_t bufsize = 128;
    char* line = malloc(bufsize);

    Grid grid;
    grid.rows = malloc(sizeof(char*) * 1024);
    grid.size = (Point){0,0};

    while (getline(&line, &bufsize, stdin) > 0) {
        grid.rows[grid.size.y] = malloc(1024);
        for (grid.size.x = 0; line[grid.size.x] != '\n'; grid.size.x++) {
            grid_set(&grid, grid.size, line[grid.size.x]);
        }

        grid.size.y++;
    }

    HashMap* map = new_hashmap(5000);
    char* save_state = malloc(100 * 100 + 1);
    int found = -1;
    for (int i = 1; i <= CYCLES; i++) {
        cycle(&grid);

        grid_inline(&grid, save_state);
        if (found == -1 && (found = hashmap_find(map, save_state)) != -1) {
            int margin = i - found;
            while (i + margin < CYCLES) i += margin;
        } else {
            hashmap_insert(map, save_state, i);
        }
    }

    printf("%zu\n", grid_north_load(&grid));
}
