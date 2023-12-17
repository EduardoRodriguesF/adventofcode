#include "lib.h"
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

size_t location_hash(const char coords[3]) {
    size_t hash = 0;

    for (int i = 0; i < 3; i++) {
        hash += (coords[i] - 'A' + 1) * i+1;
    }

    return hash;
}

struct WeakLocation read_location_line(char* line) {
    struct WeakLocation location;

    for (int i = 0; i < 3; i++) {
        location.coords[i] = *line;
        line++;
    }

    while (isspace(*line) || *line == '=' || *line == '(') line++;
    for (int i = 0; i < 3; i++) {
        location.leftcoords[i] = *line;
        line++;
    }
    location.leftcoords[3] = '\0';

    while (isspace(*line) || *line == ',') line++;
    for (int i = 0; i < 3; i++) {
        location.rightcoords[i] = *line;
        line++;
    }
    location.rightcoords[3] = '\0';

    return location;
}

void link_locations(struct LinkedLocation* buffer, struct WeakLocation weak_list[], size_t n) {
    for (size_t i = 0; i < n; i++) {
        struct WeakLocation weak = weak_list[i];
        strcpy(buffer[i].coords, weak.coords);

        for (size_t j = 0; j < n; j++) {
            if (strcmp(weak.leftcoords, weak_list[j].coords) == 0) {
                buffer[i].left = &buffer[j];
            }

            if (strcmp(weak.rightcoords, weak_list[j].coords) == 0) {
                buffer[i].right = &buffer[j];
            }
        }
    }
}

bool location_is_start(struct LinkedLocation* location) {
    return location->coords[2] == 'A';
}

bool location_is_goal(struct LinkedLocation* location) {
    return location->coords[2] == 'Z';
}
