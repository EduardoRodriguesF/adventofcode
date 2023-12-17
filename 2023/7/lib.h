#ifndef ADVENT_LIB_H
#define ADVENT_LIB_H

#include <stdlib.h>
#include <stdbool.h>

#define CARDS_LENGTH 14

typedef struct {
    size_t bid;
    char cards[5];
} Hand;

enum Type {
    HighCard,
    OnePair,
    TwoPair,
    ThreeOfAKind,
    FullHouse,
    FourOfAKind,
    FiveOfAKind,
};

enum GameResult {
    LOSE = -1,
    DRAW = 0,
    WIN = 1,
};

enum Type hand_type(const char hand[5], char joker);
int card_strength(char card);
enum GameResult play(char pivot[5], char opponent[5]);

#endif
