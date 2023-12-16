#include <ctype.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "range.h"
#include "list.h"

#define SEED_BUFSIZE 1024

struct AlmanacLine {
    Range dest;
    Range src;
};

struct AlmanacMap {
    size_t size;
    struct AlmanacLine instructions[32];
};

size_t find_lowest_location(Range seed, struct AlmanacMap* maps, size_t maps_n);

int main() {
    size_t bufsize = SEED_BUFSIZE;
    char* line = malloc(bufsize);
    char* seed_line = malloc(bufsize);
    struct Node* seed_ranges = create_node((Range){0,0});
    size_t seed_count = 0;

    struct AlmanacMap maps[bufsize];
    size_t maps_n = 0;

    // Get first line, defining seeds
    if (getline(&seed_line, &bufsize, stdin) == 0) return 1;
    while (!isdigit(*seed_line)) seed_line++;

    struct AlmanacMap* map_ptr = maps;
    map_ptr->size = 0;

    while (getline(&line, &bufsize, stdin) > 0) {
        if (*line == '\n') {
            if (map_ptr->size > 0) {
                map_ptr++;
                maps_n++;
                map_ptr->size = 0;
            }

            continue;
        }

        if (isdigit(*line)) {
            char* saved;
            struct AlmanacLine instruction;

            size_t dest_start = strtoul(strtok_r(line, " ", &saved), NULL, 0);
            size_t src_start = strtoul(strtok_r(NULL, " ", &saved), NULL, 0);
            size_t range = strtoul(strtok_r(NULL, " ", &saved), NULL, 0);

            instruction.src = create_range(src_start, src_start + range - 1);
            instruction.dest = create_range(dest_start, dest_start + range - 1);
            map_ptr->instructions[map_ptr->size++] = instruction;
        }
        char* saved;
    }

    maps_n++;

    char* saved;
    char* token = strtok_r(seed_line, " ", &saved);
    Range range = {0,0};
    size_t lowest = 0;

    size_t i = 0;
    while (token != NULL) {
        if ((++i) % 2 != 0) {
            range.start = strtoul(token, NULL, 0);
            token = strtok_r(NULL, " ", &saved);
            continue;
        }

        range.end = range.start + strtoul(token, NULL, 0) - 1;
        size_t location = find_lowest_location(range, maps, maps_n);
        if (lowest == 0 || location < lowest) lowest = location;

        token = strtok_r(NULL, " ", &saved);
    }

    printf("Lowest: %zu\n", lowest);
    list_destroy(seed_ranges);

    return 0;
}

size_t find_lowest_location(Range seed, struct AlmanacMap* maps, size_t maps_n) {
    Range lower, higher;
    struct Node* seed_ranges = create_node(seed);

    for (int map_index = 0; map_index < maps_n; map_index++) {
        struct AlmanacMap map = maps[map_index];

        // Reset flags
        for (struct Node* node = seed_ranges; node != NULL; node = node->next) node->marked = false;

        for (int j = 0; j < map.size; j++) {
            struct AlmanacLine line = map.instructions[j];

            for (struct Node* node = seed_ranges; node != NULL; node = node->next) {
                if (node->marked) continue;

                Range src = line.src;
                Range dest = line.dest;

                Range seed_range = node->value;
                Range joined = range_joined(seed_range, src);

                if (joined.start == 0 && joined.end == 0) continue;

                range_outer(seed_range, src, &lower, &higher);

                node->marked = true;

                // Save unautered ranges
                lower = range_joined(lower, node->value);
                if (lower.start != 0 && lower.end != 0) {
                    list_push(node, lower);
                }

                higher = range_joined(higher, node->value);
                if (higher.start != 0 && higher.end != 0) {
                    list_push(node, higher);
                }

                // Commit seed change
                if (src.start > dest.start) {
                    node->value.start = (joined.start - src.start) + dest.start;
                    node->value.end = (joined.end - src.end) + dest.end;
                } else {
                    node->value.start = joined.start + (dest.start - src.start);
                    node->value.end = joined.end + (dest.end - src.end);
                }
            }
        }
    }

    size_t lowest = seed_ranges->value.start;
    for (struct Node* node = seed_ranges->next; node != NULL; node = node->next) {
        if (node->value.start < lowest) lowest = node->value.start;
    }

    return lowest;
}
