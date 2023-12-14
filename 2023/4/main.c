#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WN_COUNT 10

size_t eval_scratchcard_score(char* scratchcard);
size_t count_earned_scratchcards(size_t depth, size_t solutions[], size_t n);

int main() {
    size_t bufsize = 1024;
    char* line = malloc(bufsize);
    size_t solved_scratchcards[bufsize];
    size_t unique_cards_count = 0;

    // Solve original cards
    while (getline(&line, &bufsize, stdin) > 0) {
        size_t score = eval_scratchcard_score(line);
        solved_scratchcards[unique_cards_count++] = score;
    }

    size_t total_scratchcard_count = unique_cards_count;
    for (size_t i = 0; i < unique_cards_count; i++) {
        total_scratchcard_count += count_earned_scratchcards(i, solved_scratchcards, unique_cards_count);
    }

    printf("Total scratchcards: %zu\n", total_scratchcard_count);

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
                game_score++;
                break;
            }
        }

        numbers = strtok(NULL, " ");
    }

    return game_score;
}

size_t count_earned_scratchcards(size_t depth, size_t solutions[], size_t n) {
    size_t earned = solutions[depth];
    size_t reach = depth + earned;
    size_t accumulated = 0;

    if (reach >= n) earned = reach - n;

    for (size_t i = 1; i <= earned; i++) {
        accumulated += count_earned_scratchcards(depth + i, solutions, n);
    }

    return earned + accumulated;
}
