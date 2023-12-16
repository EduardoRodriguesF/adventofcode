#ifndef ADVENT_RANGE_H
#define ADVENT_RANGE_H

#include <stdlib.h>

typedef struct {
    size_t start;
    size_t end;
} Range;

Range create_range(size_t start, size_t end);
Range range_joined(Range a, Range b);
void range_outer(Range a, Range b, Range* lower, Range* higher);

// Returns joined range and saves the lower and higher outer to pointers
Range range_group(Range a, Range b, Range* lower, Range* higher);

#endif
