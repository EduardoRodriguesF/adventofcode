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
    size_t symbols_count = 0;
    size_t candidates_count = 0;
    size_t num_length = 0;

    struct Point symbols[bufsize];

    size_t pt_count = 0;
    size_t part_number_indexes[bufsize];
    struct PartNumber candidates[bufsize];
    struct PartNumber* ptr_candidate = candidates;

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

            if (line[x] != '.' && line[x] != '\n') {
                // Symbol
                symbols[symbols_count++] = new_point(x, y);
                continue;
            }
        }

        y++;
    }

    struct Point* ptr_symbol;
    int i, j;
    for (i = 0, ptr_symbol = symbols; i < symbols_count; i++, ptr_symbol++) {
        for (j = 0, ptr_candidate = candidates; j < candidates_count; j++, ptr_candidate++) {
            size_t num_length = count_digits(ptr_candidate->value);

            struct Point diff = distance(ptr_candidate->point, *ptr_symbol);
            int diffx2 = ptr_symbol->x - (ptr_candidate->point.x + num_length - 1);

            if ((diff.x <= 1 || abs(diffx2) <= 1) && diff.y <= 1) {
                int r = add_unique(part_number_indexes, pt_count, j);
                if (r != -1) pt_count++;
            }
        }
    }

    size_t sum = 0;
    for (i = 0; i < pt_count; i++) {
        size_t pt_index =  part_number_indexes[i];
        struct PartNumber part_number = candidates[pt_index];
        sum += part_number.value;

        printf("%zu\n", part_number.value);
    }

    printf("Sum: %zu\n", sum);

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
