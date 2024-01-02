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

    reflect(grid, (Point){-1,0}, Right);

    size_t energy = 0;
    for (int y = 0; y < grid->h; y++) {
        for (int x = 0; x < grid->w; x++) {
            if (grid_at(grid, x, y)->energized) printf("#");
            else printf(".");

            energy += grid_at(grid, x, y)->energized;
        }

        printf("\n");
    }

    printf("%zu\n", energy);
}
