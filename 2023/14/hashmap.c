#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

size_t hashstr(HashMap* this, char* key) {
    size_t hash = 5381;
    char ch;
    while ((ch = *key++)) {
        hash = ((hash << 5) + hash) + ch;
    }

    return hash % this->capacity;
}

HashMap* new_hashmap(size_t capacity) {
    HashMap* this = malloc(sizeof(HashMap));
    this->capacity = capacity;
    this->length = 0;
    this->list = malloc(sizeof(HashMapEntry*) * capacity);

    return this;
}

void hashmap_insert(HashMap* this, char* key, long value) {
    size_t hashkey = hashstr(this, key);
    struct entry* entry = this->list[hashkey];

    if (entry == NULL) {
        entry = malloc(sizeof(HashMapEntry));
    } else while (entry != NULL) {
        if (entry->key != NULL && strcmp(entry->key, key) == 0) return; // Already in map

        if (entry->next == NULL) {
            entry->next = malloc(sizeof(HashMapEntry));
            break;
        }

        entry = entry->next;
    }

    entry->key = strdup(key);
    entry->value = value;
    this->list[hashkey] = entry;
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
