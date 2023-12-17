#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include "lib.h"

void sort_hands(Hand* arr, size_t n);

int main() {
    size_t linemaxsize = 16;
    char* line = malloc(linemaxsize);
    Hand* hands = malloc(1024 * sizeof(Hand));
    size_t n = 0;

    while (getline(&line, &linemaxsize, stdin) > 0) {
        char* ptr = line;
        Hand hand;

        for (int i = 0; i < 5; i++, ptr++) {
            hand.cards[i] = *ptr;
        }

        while (!isdigit(*ptr)) ptr++;

        hand.bid = atoi(ptr);

        hands[n++] = hand;
    }

    sort_hands(hands, n);

    size_t total_winnings = 0;
    for (size_t i = 0; i < n; i++) {
        size_t rank = i + 1;
        Hand hand = hands[i];

        total_winnings += hand.bid * rank;

        printf("rank %zu: %s\n", rank, hand.cards);
    }

    printf("%zu\n", total_winnings);

    free(line);
    free(hands);

    return 0;
}

void sort_hands(Hand* arr, size_t n) {
    int i, j;
    Hand pivot;

    for (i = 1; i < n; i++) {
        pivot = arr[i];
        j = i - 1;

        while (j >= 0 && play(pivot.cards, arr[j].cards) == LOSE) {
            arr[j + 1] = arr[j];
            j--;
        }

        arr[j + 1] = pivot;
    }
}
