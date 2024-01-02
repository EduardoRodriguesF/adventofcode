#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

size_t hashstr(HashMap* this, char* key) {
    int n = 0;

    while (!isspace(*key) && *key != '\0') {
        n += *key;
        n *= 17;
        n %= 256;
        key++;
    }

    return n;
}

HashMap* new_hashmap(size_t capacity) {
    HashMap* this = malloc(sizeof(HashMap));
    this->capacity = capacity;
    this->length = 0;
    this->list = malloc(sizeof(HashMapEntry*) * capacity);

    return this;
}

HashMapEntry* new_entry() {
    HashMapEntry* entry = malloc(sizeof(HashMapEntry));

    entry->value = 0;
    entry->key = NULL;
    entry->next = NULL;

    return entry;
}

void hashmap_insert(HashMap* this, char* key, long value) {
    size_t hashkey = hashstr(this, key);
    struct entry* entry = this->list[hashkey];

    if (entry == NULL) {
        entry = new_entry();
        this->list[hashkey] = entry;
    } else while (entry != NULL) {
        if (entry->key != NULL && strcmp(entry->key, key) == 0) {
            // Already in map
            entry->value = value;
            return;
        };

        if (entry->next == NULL) {
            entry->next = new_entry();
            entry = entry->next;
            break;
        }

        entry = entry->next;
    }

    entry->key = strdup(key);
    entry->value = value;
    this->length++;
}

long hashmap_find(HashMap* this, char* key) {
    size_t hashkey = hashstr(this, key);
    struct entry* entry = this->list[hashkey];

    while (entry != NULL) {
        if (entry->key != NULL && strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }

    return -1;
}

void hashmap_remove(HashMap* this, char* key) {
    size_t hashkey = hashstr(this, key);
    struct entry* entry = this->list[hashkey];
    struct entry* prev = NULL;

    while (entry != NULL) {
        if (entry->key != NULL && strcmp(entry->key, key) == 0) {
            if (prev == NULL) {
                this->list[hashkey] = entry->next;
                return;
            }

            prev->next = entry->next;
            return;
        }

        prev = entry;
        entry = entry->next;
    }
}

void hashmap_free(HashMap* this) {
    for (int i = 0; i < this->capacity; i++) {
        if (this->list[i] == NULL) continue;

        HashMapEntry* node = this->list[i]->next;
        while (node != NULL) {
            HashMapEntry* tmp = node->next;
            free(node);
            node = tmp;
        }

        free(this->list[i]);
    }

    free(this);
}
