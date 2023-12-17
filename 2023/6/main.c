#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

size_t list_numbers(char* str, size_t* buffer);
size_t win_combinations(size_t time, size_t best_distance);

int main() {
    size_t bufsize = 128;
    char* line = malloc(bufsize);

    size_t distance_list[8];
    size_t time_list[8];

    getline(&line, &bufsize, stdin);
    size_t n = list_numbers(line, time_list);

    getline(&line, &bufsize, stdin);
    list_numbers(line, distance_list);

    size_t product = 1;
    for (size_t i = 0; i < n; i++) {
        product *= win_combinations(time_list[i], distance_list[i]);
    }

    printf("%zu\n", product);

    return 0;
}

size_t list_numbers(char* str, size_t* buffer) {
    while (!isdigit(*str)) str++;
    char* token = strtok(str, " ");

    size_t i = 0;

    while (token != NULL) {
        buffer[i++] = strtoul(token, NULL, 0);

        token = strtok(NULL, " ");
    }

    return i;
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
