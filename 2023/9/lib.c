#include "lib.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int step_difference(int buf[], int sequence[], int n) {
    int rn = 0;

    for (int i = 1; i < n; ++i) {
        int a = sequence[i - 1];
        int b = sequence[i];

        buf[rn++] = b - a;
    }

    return rn;
}

bool is_bottom(int sequence[], int n) {
    for (int i = 0; i < n; i++) {
        if (sequence[i] != 0) return false;
    }

    return true;
}

int predict_next(int sequence[], int n) {
    int** tree = malloc((n+1) * sizeof(int*));
    tree[0] = sequence;
    int r, i;
    int dec_n = 0;

    for (i = 0; !is_bottom(tree[i], n - i); i++) {
        int* seq = tree[i];
        int seq_n = n - i;

        tree[i + 1] = malloc(sizeof(int) * (n + 1));
        r = step_difference(tree[i + 1], seq, seq_n);
        dec_n++;
    }

    int step = 0;
    do {
        int j = n - i;
        tree[i][j] = tree[i][j-1] + step;
        step = tree[i][j];
        i--;
    } while (i >= 0);

    for (int i = 0; i <= dec_n; i++) {
        for (int j = 0; j < n-i+1; j++) {
            if (j == n-i) printf("\033[1;31m");
            printf("%d, ", tree[i][j]);
            printf("\033[0m");
        }
        printf("\n");
    }
    printf("\n");

    return step;
}
