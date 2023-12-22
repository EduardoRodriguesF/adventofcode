#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define OPERATIONAL '.'
#define DAMAGED '#'
#define UNKNOWN '?'

typedef struct {
    char* records;
    int* damaged_groups;
    int groups_count;
} Line;

int arrengements(char* records, int* groups, int n);
bool eval_arrangement(char* records, int* groups, int n);

int main() {
    size_t bufsize = 156;
    char* line = malloc(bufsize);
    int n = 0;

    while (getline(&line, &bufsize, stdin) > 0) {
        char records[bufsize];
        int group_n, groups[16];
        group_n = 0;

        int i = 0;
        for (i = 0; *line != ' '; i++, line++) records[i] = *line;
        records[i] = '\0';
        line++;

        while (*line != '\0') {
            groups[group_n++] = atoi(line);

            while (isdigit(*line)) {
                line++;
            }
            line++;
        }

        n += arrengements(records, groups, group_n);
    }

    printf("%d\n", n);

    return 0;
}

int arrengements_r(char buffer[], char* records, int index, int records_size, int groups[], int n) {
    if (records[index] == '\0') {
        return eval_arrangement(buffer, groups, n);
    }

    if (records[index] != UNKNOWN) {
        buffer[index] = records[index];
        return arrengements_r(buffer, records, ++index, records_size, groups, n);
    }

    char abuff[records_size + 1];
    strcpy(abuff, buffer);
    abuff[index] = OPERATIONAL;
    int a = arrengements_r(abuff, records, index + 1, records_size, groups, n);

    char bbuff[records_size + 1];
    strcpy(bbuff, buffer);
    bbuff[index] = DAMAGED;
    int b = arrengements_r(bbuff, records, index + 1, records_size, groups, n);

    return a + b;
}

/**
* index - where we are at records array
*/
int arrengements(char* records, int* groups, int n) {
    int records_size = strlen(records);
    char buffer[records_size + 1];
    strcpy(buffer, records);

    return arrengements_r(buffer, records, 0, records_size, groups, n);
}

bool eval_arrangement(char* records, int* groups, int n) {
    int i = 0;
    char* token = strtok(records, ".");

    while (token != NULL) {
        if (i >= n) return false;
        if (*token != DAMAGED) break;

        int l = 0;
        while (*token == DAMAGED) {
            l++;
            token++;
        }

        if (l != groups[i]) {
            return false;
        }

        i++;
        token = strtok(NULL, ".");
    }

    return i == n;
}
