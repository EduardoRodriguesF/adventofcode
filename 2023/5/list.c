#include "list.h"
#include <stdlib.h>

struct Node* create_node(Range value) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->marked = false;
    node->value = value;

    return node;
}

void list_push(struct Node* node, Range value) {
    while (node->next != NULL) node = node->next;

    node->next = create_node(value);
}

void list_destroy(struct Node* node) {
    struct Node* tmp;

    while (node != NULL) {
        tmp = node;
        node = node->next;
        free(tmp);
    }
}
