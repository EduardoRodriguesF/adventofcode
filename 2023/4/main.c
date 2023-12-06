#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WN_COUNT 10

size_t eval_scratchcard_score(char* scratchcard);

int main() {
    size_t bufsize = 1024;
    char* line = malloc(bufsize);
    size_t total_score = 0;

    while (getline(&line, &bufsize, stdin) > 0) {
        total_score += eval_scratchcard_score(line);
    }

    printf("Total: %zu\n", total_score);

    return 0;
}

size_t eval_scratchcard_score(char* scratchcard) {
    int winning_numbers[10];

    for (; *scratchcard != ':'; scratchcard++);
    scratchcard++;

    int i = 0;
    char* numbers = strtok(scratchcard, " ");
    while (numbers != NULL && *numbers != '|') {
        winning_numbers[i++] = atoi(numbers);

        numbers = strtok(NULL, " ");
    }

    size_t game_score = 0;
    while (numbers != NULL) {
        int n = atoi(numbers);

        for (int j = 0; j < WN_COUNT; j++) {
            if (n == winning_numbers[j]) {
                if (game_score == 0) game_score++;
                else game_score *= 2;

                break;
            }
        }

        numbers = strtok(NULL, " ");
    }

    return game_score;
}
