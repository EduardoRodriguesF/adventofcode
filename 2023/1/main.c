#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, char** argv) {
    int result = 0;
    size_t bufsize = 128;
    char* buffer = malloc(bufsize);

    while (getline(&buffer, &bufsize, stdin) > 0) {
        char linenum[2];

        for (int i = 0; buffer[i] != '\0'; i++) {
            if (isdigit(buffer[i])) {
                linenum[0] = buffer[i];
                break;
            }
        }

        for (int i = strlen(buffer); i >= 0; i--) {
            if (isdigit(buffer[i])) {
                linenum[1] = buffer[i];
                break;
            }
        }

        result += atoi(linenum);
    }

    printf("%d\n", result);
}
