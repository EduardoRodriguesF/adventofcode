#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"
#include <stdlib.h>

int main() {
    size_t bufsize = 156;
    char** buffer = malloc(bufsize * bufsize);
    size_t cols = 0;
    size_t rows = 0;

    do {
        buffer[rows] = malloc(bufsize);
    } while (getline(&buffer[rows++], &bufsize, stdin) > 0);
    cols = strlen(buffer[0]);

    struct Node* entry = find_main_loop(buffer, rows, cols);

    size_t node_count = 1;
    for (struct Node* ptr = entry->next; ptr->letter != 'S'; ptr = ptr->next, node_count++);

    printf("%zu\n", node_count / 2);

    return 0;
}
