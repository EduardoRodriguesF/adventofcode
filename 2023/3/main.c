#include "point.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

size_t count_digits(size_t num);
int add_unique(size_t arr[], size_t n, size_t value);

int main() {
    size_t bufsize = 2048;
    char* line = malloc(bufsize);

    size_t x = 0;
    size_t y = 0;
    size_t gear_count = 0;
    size_t candidates_count = 0;
    size_t num_length = 0;

    struct PartNumber candidates[bufsize];
    struct PartNumber* ptr_candidate = candidates;

    struct Gear gears[bufsize];

    while (getline(&line, &bufsize, stdin) > 0) {
        for (int x = 0; line[x] != '\0'; x++) {
            if (isdigit(line[x])) {
                if (num_length == 0) {
                    *ptr_candidate = new_part_number(x, y);
                    candidates_count++;
                }

                ptr_candidate->value = (ptr_candidate->value * 10) + (line[x] - '0');

                num_length++;
                continue;
            }

            // Stopped reading number
            if (num_length > 0) {
                num_length = 0;
                ptr_candidate++;
            }

            if (line[x] == '*') {
                // Gear
                struct Gear new_gear;
                new_gear.point = new_point(x, y);

                gears[gear_count++] = new_gear;
                continue;
            }
        }

        y++;
    }

    size_t total_ratio = 0;
    struct Gear* ptr_gear;
    int i, j;
    for (i = 0, ptr_gear = gears; i < gear_count; i++, ptr_gear++) {
        size_t connections = 0;

        for (j = 0, ptr_candidate = candidates; j < candidates_count; j++, ptr_candidate++) {
            size_t num_length = count_digits(ptr_candidate->value);

            struct Point diff = distance(ptr_candidate->point, ptr_gear->point);
            int diffx2 = ptr_gear->point.x - (ptr_candidate->point.x + num_length - 1);

            if ((diff.x <= 1 || abs(diffx2) <= 1) && diff.y <= 1) {
                connections++;

                if (connections > 2) break;

                ptr_gear->pair[connections - 1] = *ptr_candidate;
            }
        }

        if (connections == 2) {
            total_ratio += gear_ratio(ptr_gear);
        }
    }

    printf("Total gear ratio: %zu\n", total_ratio);

    return 0;
}

size_t count_digits(size_t num) {
    size_t result = 0;

    do {
        result++;
    } while ((num /= 10) > 0);

    return result;
}

int add_unique(size_t arr[], size_t n, size_t value) {
    for (int i = 0; i < n; i++) if (arr[i] == value) return -1;

    arr[n] = value;
    return n;
}
