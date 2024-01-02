#include "hashmap.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

void draw_boxes(HashMap* map) {
    for (int i = 0; i < map->capacity; i++) {
        HashMapEntry* entry = map->list[i];

        if (entry == NULL) continue;

        printf("Box %d:", i);

        while (entry != NULL) {
            printf(" [%s %ld]", entry->key, entry->value);
            entry = entry->next;
        }

        printf("\n");
    }
}

int main() {
    char ch, key[16];
    size_t sum = 0, length = 0;
    HashMap* map = new_hashmap(256);

    while (1) {
        key[length] = '\0';
        length = 0;

        while (isalpha(ch = getchar())) key[length++] = ch;
        key[length] = '\0';

        if (ch == '=') {
            int lens = getchar() - '0';

            hashmap_insert(map, key, lens);
        } else if (ch == '-') {
            hashmap_remove(map, key);
        } else {
            fprintf(stderr, "Invalid operation: %c\n", ch);
            exit(1);
        }

        ch = getchar();
        if (isspace(ch) || ch == '\0') break;
        else if (ch != ',') {
            fprintf(stderr, "Something went wrong: %c\n", ch);
            exit(1);
        }
    }

    for (int i = 0; i < map->capacity; i++) {
        int boxn = i + 1;
        int slot = 1;
        HashMapEntry* entry = map->list[i];

        while (entry != NULL && entry->key != NULL && *entry->key != '\0') {
            sum += boxn * slot * entry->value;
            slot++;
            entry = entry->next;
        }
    }

    printf("%zu\n", sum);
}
