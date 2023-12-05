#include <ctype.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define COLORS_SIZE 3

char COLORS[COLORS_SIZE] = { 'r', 'g', 'b' };
size_t EXPECTED_MAXCOUNT[] = { 12, 13, 14 };

int main() {
    size_t bufsize, game_id, sum, total_power;
    bufsize = 256;
    total_power = sum = game_id = 0;

    char* line = malloc(bufsize);

    while (getline(&line, &bufsize, stdin) > 0) {
        size_t rgb_maxcount[COLORS_SIZE] = { 0, 0, 0 };

        game_id++;

        for (; *line != ':'; line++); // Skip initializer
        line++; // Skip colon

        char* round_ptr;
        char* round = strtok_r(line, ";", &round_ptr);

        while (round != NULL) {
            char* color_reveal_ptr;
            char* color_reveal = strtok_r(round, ",", &color_reveal_ptr);

            while (color_reveal != NULL) {
                size_t value = atoi(color_reveal);

                for (; isspace(*color_reveal) || isdigit(*color_reveal); color_reveal++);

                for (int j = 0; j < 3; j++) {
                    if (*color_reveal == COLORS[j] && value > rgb_maxcount[j]) {
                        rgb_maxcount[j] = value;
                        break;
                    }
                }

                color_reveal = strtok_r(NULL, ",", &color_reveal_ptr);
            }

            round = strtok_r(NULL, ";", &round_ptr);
        }

        bool is_possible = true;
        size_t power = 1;
        for (int i = 0; i < COLORS_SIZE; i++) {
            power *= rgb_maxcount[i];

            if (rgb_maxcount[i] > EXPECTED_MAXCOUNT[i]) {
                is_possible = false;
            }
        }

        if (is_possible) sum += game_id;
        total_power += power;
    }

    printf("Sum of possible Game IDs: %zu\n", sum);
    printf("Total power: %zu\n", total_power);

    return 0;
}
