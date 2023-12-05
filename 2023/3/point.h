#include <stddef.h>
#include <stdlib.h>

struct Point {
    int x;
    int y;
};

struct PartNumber {
    size_t value;
    struct Point point;
};

struct Point new_point(size_t x, size_t y);
struct PartNumber new_part_number(size_t x, size_t y);

struct Point distance(struct Point a, struct Point b);
