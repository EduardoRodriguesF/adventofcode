#ifndef ADVENT_10_LIB_H
#define ADVENT_10_LIB_H

#include <stdlib.h>
#include <stdbool.h>

#define UP (struct Point){-1,0}
#define RIGHT (struct Point){0,1}
#define DOWN (struct Point){1,0}
#define LEFT (struct Point){0,-1}

struct Point {
    int row;
    int col;
};

struct Node {
    char letter;
    struct Point point;
    struct Node* prev;
    struct Node* next;
};

typedef struct {
    struct Node* entry;
} Map;

struct Node* find_main_loop(char** data, size_t rows, size_t cols);
bool node_fits(const struct Node* a, const struct Node* b);
bool point_equals(const struct Point* a, const struct Point* b);

#endif
