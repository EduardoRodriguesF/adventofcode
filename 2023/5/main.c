#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

size_t translate(size_t seed, char** almanac_lines, size_t n);

int main() {
    size_t bufsize = 256;
    char* seed_line = malloc(bufsize);
    char* line = malloc(bufsize);
    char** lines = malloc(bufsize * sizeof(char*));
    size_t lines_num = 0;

    // Get first line, defining seeds
    if (getline(&seed_line, &bufsize, stdin) == 0) return 1;
    while (!isdigit(*seed_line)) seed_line++;

    while (getline(&line, &bufsize, stdin) > 0) {
        lines[lines_num] = malloc(bufsize);
        strcpy(lines[lines_num], line);

        lines_num++;
    }

    char* saved;
    char* token = strtok_r(seed_line, " ", &saved);
    size_t pair_seed;
    size_t i = 0;
    size_t lowest = 0;

    while (token != NULL) {
        if ((++i) % 2 != 0) {
            pair_seed = atoi(token);

            size_t seed = translate(pair_seed, lines, lines_num);
            if (lowest == 0 || seed < lowest) lowest = seed;
        } else {
            size_t range = atoi(token);
            for (size_t j = 1; j < range; j++) {
                printf("%zu out of %zu\n", j, range);
                size_t seed = translate(pair_seed + j, lines, lines_num);
                if (seed < lowest) lowest = seed;
            }
        }

        token = strtok_r(NULL, " ", &saved);
    }

    printf("Lowest: %zu\n", lowest);

    free(lines);
    free(line);
    return 0;
}

size_t translate(size_t seed, char** almanac_lines, size_t n) {
    bool has_moved = false;

    char* line = malloc(256);

    for (size_t i = 0; i < n; i++) {
        strcpy(line, almanac_lines[i]);
        char* saved;

        if (has_moved || !isdigit(*line)) {
            if (*line == '\n') has_moved = false;
            continue;
        }

        size_t dest_start = atoi(strtok_r(line, " ", &saved));
        size_t src_start = atoi(strtok_r(NULL, " ", &saved));
        size_t range = atoi(strtok_r(NULL, " ", &saved));

        size_t src_end = src_start + range - 1;

        if (seed >= src_start && seed <= src_end) {
            seed = dest_start + (seed - src_start);
            has_moved = true;
        }
    }

    return seed;
}
