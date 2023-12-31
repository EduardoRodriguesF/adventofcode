#include <stdio.h>
short holiday_hash(char* str) {
    int n = 0;

    while (*str != '\0' && *str != '\n') {
        n += *str;
        n *= 17;
        n %= 256;
        str++;
    }

    return n;
}

int main() {
    char ch, entry[16];
    size_t sum = 0, length = 0;

    while (1) {
        ch = getchar();

        if (ch != ',' && ch != '\0' && ch != '\n') {
            entry[length++] = ch;
            continue;
        }

        entry[length] = '\0';
        length = 0;
        sum += holiday_hash(entry);

        if (ch == '\0' || ch == '\n') break;
    }

    printf("%zu\n", sum);
}
