#include "point.h"
#include <stdlib.h>

struct Point new_point(size_t x, size_t y) {
    struct Point point;
    point.x = x;
    point.y = y;

    return point;
}

struct PartNumber new_part_number(size_t x, size_t y) {
    struct PartNumber part_num;
    part_num.point = new_point(x, y);
    part_num.value = 0;

    return part_num;
}

struct Point distance(struct Point a, struct Point b) {
    struct Point result;
    result.x = abs(a.x - b.x);
    result.y = abs(a.y - b.y);

    return result;
}
