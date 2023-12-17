#ifndef ADVENT_8_LIB_H
#define ADVENT_8_LIB_H

#include <stdlib.h>

struct WeakLocation {
    char coords[4];
    char leftcoords[4];
    char rightcoords[4];
};

struct LinkedLocation {
    char coords[4];
    struct LinkedLocation* left;
    struct LinkedLocation* right;
};

size_t location_hash(const char coords[3]);
struct WeakLocation read_location_line(char* line);
void link_locations(struct LinkedLocation* buffer, struct WeakLocation weak_arr[], size_t n);

#endif
