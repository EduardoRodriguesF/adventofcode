#include "lcm.h"
#include "lib.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LEFT 'L'
#define RIGHT 'R'

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

    struct LinkedLocation ghost_locations[bufsize/2];
    size_t ghost_n = 0;
    for (int i = 0; i < n; i++) {
        if (location_is_start(&linked_locations[i])) ghost_locations[ghost_n++] = linked_locations[i];
    }

    size_t required_steps[ghost_n];

    for (int g = 0; g < ghost_n; g++) {
        struct LinkedLocation* ptr = &ghost_locations[g];
        int steps = 0;
        bool reached = false;

        while (!reached) {
            for (int i = 0; move_stack[i] != '\0'; i++) {
                if (isspace(move_stack[i])) continue;
                steps++;

                if (move_stack[i] == LEFT) *ptr = *ptr->left;
                else if (move_stack[i] == RIGHT) *ptr = *ptr->right;

                if (location_is_goal(ptr)) {
                    reached = true;
                    break;
                }
            }
        }

        required_steps[g] = steps;
    }

    printf("%zu\n", lcm(required_steps, ghost_n));

    return 0;
}
