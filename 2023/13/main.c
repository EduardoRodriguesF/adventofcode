#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_ROWS 512

#define ASH '.'
#define ROCK '#'

#define REV(c) (c == ASH ? ROCK : ASH)

typedef struct grid {
    char** rows;
    size_t w, h;
} Grid;

typedef enum reflection_t {
    Vertical,
    Horizontal,
} ReflectionType;

void push_row(Grid* grid, char* data) {
    int i = 0;
    char* row = malloc(grid->w + 1);

    while (*data != '\n' && *data != '\0') row[i++] = *data++;

    if (!grid->w) grid->w = i;
    grid->rows[grid->h] = malloc(i);
    grid->rows[grid->h] = row;

    grid->h++;
}

int find_horizontal_reflection_index(const Grid* grid, int ignore) {
    int a, b, target;
    bool match;

    for (target = 0; target < grid->h - 1; target++) {
        if (target == ignore) continue;

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

int find_vertical_reflection_index(const Grid* grid, int ignore) {
    int a, b, target;
    bool match;

    for (target = 0; target < grid->w - 1; target++) {
        if (target == ignore) continue;

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

int fix_smudge(Grid* grid) {
    int prev;
    ReflectionType dir;
    int (*samedir_fn)(const Grid*, int);
    int (*opposite_fn)(const Grid*, int);
    if ((prev = find_vertical_reflection_index(grid, -1)) != -1) {
        dir = Vertical;
        samedir_fn = find_vertical_reflection_index;
        opposite_fn = find_horizontal_reflection_index;
    } else {
        dir = Horizontal;
        prev = find_horizontal_reflection_index(grid, -1);
        samedir_fn = find_horizontal_reflection_index;
        opposite_fn = find_vertical_reflection_index;
    }

    for (int i = 0; i < grid->h; i++) {
        char* row = grid->rows[i];

        for (int col = 0; col < grid->w; col++) {
            row[col] = REV(row[col]);

            int v;
            if ((v = opposite_fn(grid, -1)) != -1) {
                return (v+1) * (dir == Vertical ? 100 : 1);
            };

            if ((v = samedir_fn(grid, prev)) != -1 && v != prev) {
                return (v+1) * (dir == Horizontal ? 100 : 1);
            }
            // Back to normal
            row[col] = REV(row[col]);
        }
    }

    fprintf(stderr, "could not find smudge\n");
    exit(1);
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

        result += fix_smudge(&grid);

        grid.h = 0;
        grid.w = 0;
    } while (line_length > 0);

    printf("%ld\n", result);

    return 0;
}
