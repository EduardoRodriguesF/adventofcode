#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include <stdlib.h>

bool can_go_out_of_bounds(struct Point pos, char** grid, struct Point size);

int main() {
    size_t bufsize = 156;
    char** buffer = malloc(bufsize * bufsize);
    size_t cols = 0;
    size_t rows = 0;

    do {
        buffer[rows] = malloc(bufsize);
    } while (getline(&buffer[rows++], &bufsize, stdin) > 0);
    cols = strlen(buffer[0]);

    struct Node* entry;
    int node_count = find_main_loop(entry, buffer, rows, cols);

    struct Point highest, lowest;
    highest = lowest = (struct Point){entry->point.row, entry->point.col};

    for (struct Node* ptr = entry->next; ptr->letter != 'S'; ptr = ptr->next) {
        if (ptr->point.col > highest.col) highest.col = ptr->point.col;
        else if (ptr->point.col < lowest.col) lowest.col = ptr->point.col;

        if (ptr->point.row > highest.row) highest.row = ptr->point.row;
        else if (ptr->point.row < lowest.row) lowest.row = ptr->point.row;
    }

    int r, c;
    // Replace main loop's blocks with something recognizable
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            struct Point point = {r, c};
            struct Node* node = entry;
            bool has_wall = false;
            do {
                if (point_equals(&node->point, &point)) {
                    has_wall = true;
                    break;
                }

                node = node->next;
            } while (node->letter != 'S');

            if (!has_wall) buffer[r][c] = '.';
        }
    }

    struct Point vertices[node_count];
    int n_vert = calc_vertices(vertices, entry);

    int tiles = 0;
    struct Point size = {rows, cols};
    for (r = 0; r < rows; r++) {
        for (c = 0; c < cols; c++) {
            struct Point point = {r, c};

            if (buffer[r][c] == '.') {
                if (point_in_polygon(point, vertices, n_vert)) {
                    printf("I");
                    tiles++;
                } else printf(".");
            } else printf("%c", buffer[r][c]);
        }

        printf("\n");
    }

    printf("%d\n", tiles);

    return 0;
}
