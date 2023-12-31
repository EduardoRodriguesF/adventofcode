#include <stdbool.h>
#include <stdio.h>
#include "grid.h"

bool point_equals(const Point a, const Point b) {
    return a.x == b.x && a.y == b.y;
}

char grid_at(const Grid* this, Point point) {
    return this->rows[point.y][point.x];
}

void grid_set(Grid* this, Point point, char c) {
    this->rows[point.y][point.x] = c;
}

void grid_move(Grid* this, Point from, Point to) {
    if (from.x == to.x && from.y == to.y) return;

    if (grid_at(this, from) != ROLLING || grid_at(this, to) != EMPTY) {
        fprintf(stderr, "Failed to move point: (%zu,%zu) -> (%zu,%zu)\n", from.x, from.y, to.x, to.y);
        exit(1);
    }

    grid_set(this, from, EMPTY);
    grid_set(this, to, ROLLING);
}

void grid_inline(Grid* this, char* buffer) {
    int i = 0;
    for (int y = 0; y < this->size.y; y++) {
        for (int x = 0; x < this->size.x; x++) {
            buffer[i++] = grid_at(this, (Point){x,y});
        }
    }
}

void grid_draw(Grid* this) {
    for (int y = 0; y < this->size.y; y++) {
        for (int x = 0; x < this->size.x; x++) {
            printf("%c", grid_at(this, (Point){x,y}));
        }

        printf("\n");
    }
}

size_t grid_north_load(const Grid* this) {
    size_t sum = 0;
    for (int y = 0; y < this->size.y; y++) {
        for (int x = 0; x < this->size.x; x++) {
            if (grid_at(this, (Point){x,y}) == ROLLING) {
                sum+= this->size.y - y;
            }
        }
    }

    return sum;
}

void grid_tilt_north(Grid* this) {
    for (int y = 1; y < this->size.y; y++) {
        for (int x = 0; x < this->size.x; x++) {
            Point origin = {x,y};
            Point dest = origin;
            if (grid_at(this, dest) != ROLLING) continue;

            while (dest.y > 0) {
                if (grid_at(this, (Point){dest.x, dest.y - 1}) == EMPTY) dest.y--;
                else break;
            }

            grid_move(this, origin, dest);
        }
    }
}

void grid_tilt_west(Grid* this) {
    for (int x = 1; x < this->size.x; x++) {
        for (int y = 0; y < this->size.y; y++) {
            Point origin = {x,y};
            Point dest = origin;
            if (grid_at(this, dest) != ROLLING) continue;

            while (dest.x > 0) {
                if (grid_at(this, (Point){dest.x - 1, y}) == EMPTY) dest.x--;
                else break;
            }

            grid_move(this, origin, dest);
        }
    }
}

void grid_tilt_south(Grid* this) {
    for (int y = this->size.y - 1; y >= 0; y--) {
        for (int x = 0; x < this->size.x; x++) {
            Point origin = {x,y};
            Point dest = origin;
            if (grid_at(this, dest) != ROLLING) continue;

            while (dest.y < this->size.y - 1) {
                if (grid_at(this, (Point){dest.x, dest.y + 1}) == EMPTY) dest.y++;
                else break;
            }

            grid_move(this, origin, dest);
        }
    }
}

void grid_tilt_east(Grid* this) {
    for (int x = this->size.x - 1; x >= 0; x--) {
        for (int y = 0; y < this->size.y; y++) {
            Point origin = {x,y};
            Point dest = origin;
            if (grid_at(this, dest) != ROLLING) continue;

            while (dest.x < this->size.x) {
                if (grid_at(this, (Point){dest.x + 1, y}) == EMPTY) dest.x++;
                else break;
            }

            grid_move(this, origin, dest);
        }
    }
}
