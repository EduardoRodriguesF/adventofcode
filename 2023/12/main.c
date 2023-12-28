#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"

#define OPERATIONAL '.'
#define DAMAGED '#'
#define UNKNOWN '?'

#define MEMO_BUFFER 7000
#define RECORD_SIZE 128

long arrengements(char* records, int* groups, int n);
bool eval_arrangement(char* records, int* groups, int n);
int unfold(char* records, int n, int folds);
int unfold_groups(int* groups, int n, int folds);

char* simplify(char* records);

int main(int argc, char** argv) {
    int folds = argc > 1 ? atoi(argv[1]) : 1;
    size_t bufsize = 528;
    char* line = malloc(bufsize);
    long n = 0;

    while (getline(&line, &bufsize, stdin) > 0) {
        char records[bufsize];
        int group_n, groups[64];
        group_n = 0;

        int i = 0;
        for (i = 0; *line != ' '; i++, line++) records[i] = *line;
        unfold(records, i, folds);
        line++;

        while (*line != '\0') {
            groups[group_n++] = atoi(line);

            while (isdigit(*line)) {
                line++;
            }
            line++;
        }

        group_n = unfold_groups(groups, group_n, folds);
        n += arrengements(records, groups, group_n);
    }

    printf("%ld\n", n);

    return 0;
}

long arrengements_r(char buffer[], bool unknowns[], int index, int records_size, int groups[], int n, HashMap* map) {
    long result = 0;
    while (buffer[index] != '\0' && !unknowns[index]) index++;

    if (buffer[index] == '\0') {
        return eval_arrangement(buffer, groups, n);
    }

    buffer[index] = OPERATIONAL;
    if (eval_arrangement(buffer, groups, n)) {
        char* key = simplify(buffer);
        long v = hashmap_find(map, key);
        if (v == -1) {
            v = arrengements_r(buffer, unknowns, index + 1, records_size, groups, n, map);
            hashmap_insert(map, key, v);
        }

        result += v;
    }

    for (int i = index + 1; i < records_size; i++)
        if (unknowns[i]) buffer[i] = UNKNOWN;

    buffer[index] = DAMAGED;
    if (eval_arrangement(buffer, groups, n)) {
        char* key = simplify(buffer);
        long v = hashmap_find(map, key);
        if (v == -1) {
            v = arrengements_r(buffer, unknowns, index + 1, records_size, groups, n, map);
            hashmap_insert(map, key, v);
        }

        result += v;
    }

    return result;
}

long arrengements(char* records, int* groups, int n) {
    int records_size = strlen(records);
    bool unknowns[records_size];
    HashMap* map = new_hashmap(MEMO_BUFFER);;

    for (int i = 0; i < records_size; i++) {
        unknowns[i] = records[i] == UNKNOWN;
    }

    long v = arrengements_r(records, unknowns, 0, records_size, groups, n, map);

    hashmap_free(map);

    return v;
}

bool eval_arrangement(char* records, int* groups, int n) {
    int i = 0;
    char* ptr = records;

    while (true) {
        while (*ptr == OPERATIONAL) ptr++;
        if (*ptr == '\0') break;

        int l = 0;
        while (*ptr == DAMAGED) {
            l++;
            ptr++;
        }

        if (*ptr == UNKNOWN && l <= groups[i]) return true;

        if (l != groups[i]) return false;

        i++;
    }

    return i == n;
}

int unfold(char* records, int n, int folds) {
    int size = n;

    for (int f = 1; f < folds; f++) {
        records[size++] = UNKNOWN;

        for (int i = 0; i < n; i++) {
            records[size + i] = records[i];
        }

        size += n;
    }

    records[size] = '\0';

    return size;
}

int unfold_groups(int* groups, int n, int folds) {
    int size = n;

    for (int f = 1; f < folds; f++) {
        for (int i = 0; i < n; i++) {
            groups[size + i] = groups[i];
        }
        size += n;
    }

    return size;
}

char* simplify(char* records) {
    int n = 0;
    int i = 0;
    char* buffer = malloc(RECORD_SIZE);

    while (records[i] != '\0') {
        buffer[n++] = records[i];

        if (records[i] != OPERATIONAL) i++;
        else while (records[i] == OPERATIONAL) i++;
    }

    buffer[n] = '\0';

    return buffer;
}
