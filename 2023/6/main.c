#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t atoi_with_bad_kerning(char* str);
size_t win_combinations(size_t time, size_t best_distance);

int main() {
    size_t bufsize = 128;
    char* line = malloc(bufsize);

    getline(&line, &bufsize, stdin);
    size_t time = atoi_with_bad_kerning(line);

    getline(&line, &bufsize, stdin);
    size_t distance = atoi_with_bad_kerning(line);

    size_t combinations = win_combinations(time, distance);

    printf("%zu\n", combinations);

    return 0;
}

size_t atoi_with_bad_kerning(char* str) {
    size_t result = 0;

    while (*str != '\0') {
        if (isdigit(*str)) result = (result * 10) + (*str - '0');
        str++;
    }

    return result;
}

size_t win_combinations(size_t time, size_t best_distance) {
    size_t combinations = 0;

    for (size_t i = 1; i < time; i++) {
        size_t speed = i;
        size_t remaining_time = time - i;

        size_t distance = speed * remaining_time;

        if (distance > best_distance) combinations++;
    }

    return combinations;
}
