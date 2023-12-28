#ifndef ADVENT_HASHMAP_H
#define ADVENT_HASHMAP_H

#include <stdlib.h>

typedef struct entry {
    char* key;
    long value;
    struct entry* next;
} HashMapEntry;

typedef struct hashmap {
    HashMapEntry** list;
    size_t capacity;
    size_t length;
} HashMap;

HashMap* new_hashmap(size_t capacity);
void hashmap_insert(HashMap* map, char* key, long value);
long hashmap_find(HashMap* map, char* key);
void hashmap_free(HashMap* map);

#endif
