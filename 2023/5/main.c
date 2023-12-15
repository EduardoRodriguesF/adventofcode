#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int main() {
    size_t bufsize = 1024;
    char* line;

    size_t seeds[128];
    size_t n = 0;

    // Get first line, defining seeds
    if (getline(&line, &bufsize, stdin) == 0) return 1;
    char* token = strtok(line, " ");

    while (token != NULL) {
        if (isdigit(*token)) {
            seeds[n++] = atoi(token);
        }

        token = strtok(NULL, " ");
    }

    bool seeds_moved[n];

    // Process movements
    while (getline(&line, &bufsize, stdin) > 0) {
        if (*line == '\n') {
            // Reset flags
            for (int i = 0; i < n; i++) seeds_moved[i] = false;
            continue;
        }

        if (isdigit(*line)) {

            size_t dest_start = atoi(strtok(line, " "));
            size_t src_start = atoi(strtok(NULL, " "));
            size_t range = atoi(strtok(NULL, " "));

            size_t src_end = src_start + range - 1;

            for (size_t i = 0; i < n; i++) {
                size_t seed = seeds[i];

                if (!seeds_moved[i] && seed >= src_start && seed <= src_end) {
                    size_t offset = seed - src_start;
                    seeds[i] = dest_start + offset;
                    seeds_moved[i] = true;
                }
            }

            continue;
        }
    }

    size_t lowest = seeds[0];
    for (size_t i = 1; i < n; i++) {
        if (seeds[i] < lowest) lowest = seeds[i];
    }

    printf("Lowest: %zu\n", lowest);

    return 0;
}
