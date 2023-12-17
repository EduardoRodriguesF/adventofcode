#include "lib.h"

char CARDS[CARDS_LENGTH] = "J23456789TQKA";

enum Type hand_type(const char hand[5], char joker) {
    enum Type type = HighCard;
    int card_count[CARDS_LENGTH] = { 0 };

    size_t highest_strength = 0;
    for (int i = 0; i < 5; i++) {
        int strength = card_strength(hand[i]);
        card_count[strength]++;

        if (hand[i] != joker && (highest_strength == 0 || card_count[strength] > card_count[highest_strength])) {
            highest_strength = strength;
        }
    }

    if (joker != 0) {
        // damn it edge case
        if (card_count[card_strength(joker)] == 5) return FiveOfAKind;

        int joker_strength = card_strength(joker);
        card_count[highest_strength] += card_count[joker_strength];
        card_count[joker_strength] -= card_count[joker_strength];
    }

    for (int i = 0; i < CARDS_LENGTH; i++) {
        int count = card_count[i];

        if (count == 5) return FiveOfAKind;
        if (count == 4) return FourOfAKind;

        if (count == 3) {
            if (type == OnePair) return FullHouse;

            type = ThreeOfAKind;
        } else if (count == 2) {
            if (type == ThreeOfAKind) return FullHouse;
            if (type == OnePair) return TwoPair;

            type = OnePair;
        }
    }

    return type;
}

int card_strength(char card) {
    for (int i = 0; CARDS[i] != '\0'; i++) {
        if (card == CARDS[i]) return i;
    }

    return -1;
}

enum GameResult play(char pivot[5], char opponent[5]) {
    enum Type pivot_type = hand_type(pivot, 'J');
    enum Type opponent_type = hand_type(opponent, 'J');
    if (pivot_type != opponent_type) return pivot_type > opponent_type ? WIN : LOSE;

    for (int i = 0; i < 5; i++) {
        int spivot = card_strength(pivot[i]);
        int sopponent = card_strength(opponent[i]);

        if (spivot != sopponent) return spivot > sopponent ? WIN : LOSE;
    }

    return DRAW;
}
