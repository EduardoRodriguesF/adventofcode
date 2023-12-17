#include "lib.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LEFT 'L'
#define RIGHT 'R'
#define START "AAA"
#define GOAL "ZZZ"

int main() {
    size_t bufsize = 512;
    char* line = malloc(bufsize);
    char move_stack[bufsize];
    size_t n = 0;

    struct WeakLocation* weak_locations = malloc(1024 * sizeof(struct WeakLocation));
    struct LinkedLocation* linked_locations = malloc(1024 * sizeof(struct LinkedLocation));

    getline(&line, &bufsize, stdin);
    int ri = 0;
    for (int i = 0; line[i] != '\0'; i++) {
        if (line[i] == LEFT || line[i] == RIGHT) move_stack[ri++] = line[i];
    }

    while (getline(&line, &bufsize, stdin) > 0) {
        if (*line == '\n') continue;

        struct WeakLocation location = read_location_line(line);
        weak_locations[n++] = location;
    }

    link_locations(linked_locations, weak_locations, n);
    free(weak_locations);

    struct LinkedLocation* ptr = linked_locations;
    while (strcmp(ptr->coords, START) != 0) ptr++;

    size_t steps = 0;
    bool reached = false;
    while (!reached) {
        for (int i = 0; move_stack[i] != '\0'; i++) {
            steps++;
            if (move_stack[i] == LEFT) ptr = ptr->left;
            else if (move_stack[i] == RIGHT) ptr = ptr->right;

            if (strcmp(GOAL, ptr->coords) == 0) {
                reached = true;
                break;
            }
        }
    }

    printf("%zu\n", steps);

    return 0;
}
