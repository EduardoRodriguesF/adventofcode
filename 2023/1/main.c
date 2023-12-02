#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>

char* DIGITS[] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

int word_to_digit(const char* str);
char read_digit(const char* str);

int main(int argc, char** argv) {
    int result = 0;
    size_t bufsize = 128;
    char* buffer = malloc(bufsize);

    while (getline(&buffer, &bufsize, stdin) > 0) {
        char linenum[2];

        for (int i = 0; buffer[i] != '\0'; i++) {
            char digit = read_digit(&buffer[i]);

            if (digit != '\0') {
                linenum[0] = digit;
                break;
            }
        }

        for (int i = strlen(buffer); i >= 0; i--) {
            char digit = read_digit(&buffer[i]);

            if (digit != '\0') {
                linenum[1] = digit;
                break;
            }
        }

        result += atoi(linenum);
    }

    printf("%d\n", result);
}

char read_digit(const char* str) {
    if (isdigit(str[0])) return str[0];

    int digit = word_to_digit(str);
    if (digit != -1) return digit + '0';

    return '\0';
}

int word_to_digit(const char* str) {
    for (int digit = 0; digit <= 9; digit++) {
        bool match = true;
        char* strdigit = DIGITS[digit];

        for (int i = 0; strdigit[i] != '\0'; i++) {
            if (str[i] != strdigit[i]) {
                match = false;
                break;
            }
        }

        if (match) {
            return digit;
        }
    }

    return -1;
}
