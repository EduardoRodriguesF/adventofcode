#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

struct AlmanacLine {
    size_t dest;
    size_t src;
    size_t range;
};

struct AlmanacMap {
    struct AlmanacLine* instructions;
    size_t size;
};

size_t translate(size_t seed, struct AlmanacMap maps[], size_t n);

int main() {
    size_t bufsize = 256;
    char* seed_line = malloc(bufsize);
    char* line = malloc(bufsize);

    struct AlmanacMap maps[bufsize];
    size_t maps_n = 0;

    // Get first line, defining seeds
    if (getline(&seed_line, &bufsize, stdin) == 0) return 1;
    while (!isdigit(*seed_line)) seed_line++;

    struct AlmanacMap* map_ptr = maps;
    map_ptr->instructions = malloc(32 * sizeof(struct AlmanacLine));
    map_ptr->size = 0;

    while (getline(&line, &bufsize, stdin) > 0) {
        if (*line == '\n') {
            if (map_ptr->size > 0) {
                map_ptr++;
                maps_n++;

                map_ptr->instructions = malloc(32 * sizeof(struct AlmanacLine));
                map_ptr->size = 0;
            }
            continue;
        }

        if (isdigit(*line)) {
            char* saved;
            struct AlmanacLine instruction;

            instruction.dest = atoi(strtok_r(line, " ", &saved));
            instruction.src = atoi(strtok_r(NULL, " ", &saved));
            instruction.range = atoi(strtok_r(NULL, " ", &saved));

            map_ptr->instructions[map_ptr->size++] = instruction;
        }
        char* saved;
    }

    maps_n++;

    char* saved;
    char* token = strtok_r(seed_line, " ", &saved);
    size_t pair_seed;
    size_t i = 0;
    size_t lowest = 0;

    while (token != NULL) {
        if ((++i) % 2 != 0) {
            pair_seed = atoi(token);

            size_t seed = translate(pair_seed, maps, maps_n);
            if (lowest == 0 || seed < lowest) lowest = seed;
        } else {
            size_t range = atoi(token);
            for (size_t j = 1; j < range; j++) {
                printf("%zu out of %zu\n", j, range);
                size_t seed = translate(pair_seed + j, maps, maps_n);
                if (seed < lowest) lowest = seed;
            }
        }

        token = strtok_r(NULL, " ", &saved);
    }

    printf("Lowest: %zu\n", lowest);

    return 0;
}

size_t translate(size_t seed, struct AlmanacMap maps[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        struct AlmanacMap map = maps[i];

        for (size_t j = 0; j < map.size; j++) {
            struct AlmanacLine line = map.instructions[j];

            size_t src_end = line.src + line.range - 1;

            if (seed >= line.src && seed <= src_end) {
                seed = line.dest + (seed - line.src);
                break;
            }
        }
    }

    return seed;
}
