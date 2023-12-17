#include "lib.h"
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    size_t bufsize = 256;
    char* line = malloc(bufsize);
    size_t result = 0;

    while (getline(&line, &bufsize, stdin) > 0) {
        int sequence[bufsize];
        int n = 0;

        char* save;
        char* token = strtok_r(line, " ", &save);
        while (token != NULL) {
            sequence[n++] = atoi(token);

            token = strtok_r(NULL, " ", &save);
        }

        if (n > 0) result += predict_next(sequence, n);
    }

    printf("%zu\n", result);

    return 0;
}
