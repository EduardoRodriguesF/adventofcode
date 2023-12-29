#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 512

typedef struct grid {
    char** rows;
    size_t w, h;
} Grid;

void push_row(Grid* grid, char* data) {
    int i = 0;
    char* row = malloc(grid->w + 1);

    while (*data != '\n' && *data != '\0') row[i++] = *data++;

    if (!grid->w) grid->w = i;
    grid->rows[grid->h] = malloc(i);
    grid->rows[grid->h] = row;

    grid->h++;
}

int find_horizontal_reflection_index(const Grid* grid) {
    int a, b, target;
    bool match;

    for (target = 0; target < grid->h - 1; target++) {
        match = true;
        a = target;
        b = target + 1;

        do {
            if (strcmp(grid->rows[a], grid->rows[b]) != 0) {
                match = false;
                break;
            }

            a--, b++;
        } while (a >= 0 && b < grid->h);

        if (match) return target;
    }

    return -1;
}

int find_vertical_reflection_index(const Grid* grid) {
    int a, b, target;
    bool match;

    for (target = 0; target < grid->w - 1; target++) {
        match = true;
        a = target;
        b = target + 1;

        do {
            for (int row = 0; row < grid->h; row++) {
                if (grid->rows[row][a] != grid->rows[row][b]) {
                    match = false;
                    break;
                }
            }

            if (!match) break;

            a--, b++;
        } while (a >= 0 && b < grid->w);

        if (match) return target;
    }

    return -1;
}

int main() {
    size_t bufsize = 128;
    char* line = malloc(bufsize);
    long result = 0;

    int line_length;
    Grid grid;
    grid.w = grid.h = 0;
    grid.rows = malloc(MAX_ROWS * sizeof(char*));
    do {
        line_length = getline(&line, &bufsize, stdin);

        if (*line != '\n' && line_length > 0) {
            push_row(&grid, line);
            continue;
        }

        int reflection, n;
        n = 0;
        if ((reflection = find_vertical_reflection_index(&grid)) != -1) {
            n = reflection + 1;
        } else if ((reflection = find_horizontal_reflection_index(&grid)) != -1) {
            n = (reflection + 1) * 100;
        }

        grid.h = 0;
        grid.w = 0;

        result += n;
    } while (line_length > 0);

    printf("%ld\n", result);

    return 0;
}
