#ifndef ADVENT_LIST_H
#define ADVENT_LIST_H

#include <stdbool.h>
#include "range.h"

struct Node {
    Range value;
    bool marked;
    struct Node* next;
};

struct Node* create_node(Range value);
void list_push(struct Node* node, Range value);
void list_destroy(struct Node* node);

#endif
