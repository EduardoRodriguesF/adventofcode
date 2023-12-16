#ifndef ADVENT_RANGE_H
#define ADVENT_RANGE_H

#include <stdlib.h>

typedef struct {
    int start;
    int end;
} Range;

Range create_range(int start, int end);
Range range_joined(Range a, Range b);
void range_outer(Range a, Range b, Range* lower, Range* higher);

#endif
