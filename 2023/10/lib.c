#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const struct Point DIRECTIONS[4] = {UP, RIGHT, DOWN, LEFT};

struct Node* find_main_loop(char** data, size_t rows, size_t cols) {
    struct Node* entry = malloc(sizeof(struct Node));

    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            if (data[r][c] == 'S') {
                entry->letter = 'S';
                entry->point.row = r;
                entry->point.col = c;
                entry->prev = NULL;
                entry->next = NULL;

                goto found_entry;
            }
        }
    }
found_entry:;

    struct Node cmp;
    struct Node* ptr = entry;
    do {
        for (int i = 0; i < 4; i++) {
            cmp.point = DIRECTIONS[i];
            cmp.point.row += ptr->point.row;
            cmp.point.col += ptr->point.col;
            cmp.prev = NULL;
            cmp.next = NULL;

            // Avoid infinite loop between two connected pieces
            if (ptr->prev != NULL && point_equals(&ptr->prev->point, &cmp.point)) {
                continue;
            }

            if (cmp.point.row < -1 || cmp.point.col < -1 || cmp.point.row >= rows || cmp.point.col >= cols)
                continue;

            cmp.letter = data[cmp.point.row][cmp.point.col];

            if (node_fits(ptr, &cmp)) {
                struct Node* node;
                if (point_equals(&entry->point, &cmp.point)) {
                    node = entry;
                } else {
                    node = malloc(sizeof(struct Node));
                    memcpy(node, &cmp, sizeof(struct Node));
                }

                node->prev = ptr;
                ptr->next = node;
                break;
            }
        }

        ptr = ptr->next;
    } while (ptr->letter != 'S');

    return entry;
}

bool node_fits(const struct Node* a, const struct Node* b) {
    struct Point ab_diff = {
        b->point.row - a->point.row,
        b->point.col - a->point.col
    };

    if (point_equals(&ab_diff, &DOWN)) {
        /**
        * . B
        * . A
        */
        return (
            (a->letter == 'S' || a->letter == '|' || a->letter == '7' || a->letter == 'F') &&
            (b->letter == 'S' || b->letter == '|' || b->letter == 'J' || b->letter == 'L')
        );
    }

    if (point_equals(&ab_diff, &UP)) {
        /**
        * . A
        * . B
        */
        return (
            (a->letter == 'S' || a->letter == '|' || a->letter == 'J' || a->letter == 'L') &&
            (b->letter == 'S' || b->letter == '|' || b->letter == '7' || b->letter == 'F')
        );
    } 

    if (point_equals(&ab_diff, &RIGHT)) {
        /**
        * A B
        * . .
        */
        return (
            (a->letter == 'S' || a->letter == '-' || a->letter == 'L' || a->letter == 'F') &&
            (b->letter == 'S' || b->letter == '-' || b->letter == 'J' || b->letter == '7')
        );
    }

    if (point_equals(&ab_diff, &LEFT)) {
        /**
        * A B
        * . .
        */
        return (
            (a->letter == 'S' || a->letter == '-' || a->letter == 'J' || a->letter == '7') &&
            (b->letter == 'S' || b->letter == '-' || b->letter == 'L' || b->letter == 'F')
        );
    }
    
    return false;
}

bool point_equals(const struct Point* a, const struct Point* b) {
    return a->row == b->row && a->col == b->col;
}
