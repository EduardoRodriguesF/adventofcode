#include "range.h"
#include <stdio.h>

Range create_range(int start, int end) {
    Range range = {start, end};
    return range;
}

Range range_joined(Range a, Range b) {
    Range joined = {-1, -1};

    if (a.start >= b.start && a.start <= b.end) {
        joined.start = a.start;
    } else if (b.start >= a.start && b.start <= a.end) {
        joined.start = b.start;
    }

    if (a.end <= b.end && a.end >= b.start) {
        joined.end = a.end;
    } else if (b.end <= a.end && b.end >= a.start) {
        joined.end = b.end;
    }

    return joined;
}

void range_outer(Range a, Range b, Range* lower, Range* higher) {
    lower->start = -1;
    if (a.start < b.start) {
        lower->start = a.start;
    } else if (a.start > b.start) {
        lower->start = b.start;
    }

    if (a.start < b.start) {
        lower->start = a.start;

        if (a.end >= b.start) {
            lower->end = b.start - 1;
        } else {
            lower->end = a.end;
        }
    } else if (a.start > b.start) {
        lower->start = b.start;

        if (b.end >= a.start) {
            lower->end = a.start - 1;
        } else {
            lower->end = b.end;
        }
    } else {
        lower->start = -1;
        lower->end = -1;
    }

    if (a.end > b.end) {
        higher->end = a.end;

        if (b.start <= a.end) {
            higher->start = b.end + 1;
        } else {
            higher->end = a.start;
        }
    } else if (a.end < b.end) {
        higher->end = b.end;

        if (a.start <= b.end) {
            higher->start = a.end + 1;
        } else {
            higher->end = b.start;
        }
    } else {
        higher->start = -1;
        higher->end = -1;
    }
}
