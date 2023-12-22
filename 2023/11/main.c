/**
* [x] - Expand universe
*   - Each row and col that does not contain a galaxy needs to be expanded
*   - Be careful not to infinitely add space. For each added space, immediatly place `i` into the new row/col. This way, next
*   iteration will be on the unpassed row/col.
* [x] - Separate pairs
*   - Cannot duplicate pairs (e.g. {1,2} and {2,1}. To make it work, for i and j in pair, always start j at i+1
* [ ] - Calculate distances
*   - Distance to get to the same row and then distance to get to the same col. Nothing sophisticated.
*   - Maybe it can be done with two subtractions?
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t x, y; 
} Point;

void draw_universe(Point galaxies[], int n, Point size);
size_t distance(Point a, Point b);

int main(int argc, char** argv) {
    if (argc <= 1) {
        fprintf(stderr, "Missing expansion argument");
        return 1;
    }

    size_t expansion = atoi(argv[1]) - 1;
    size_t bufsize = 1024;
    char* line = malloc(bufsize);
    Point galaxies[bufsize*4];
    size_t n = 0;

    Point size = {0,0};
    while (getline(&line, &bufsize, stdin) > 0) {
        for (size.x = 0; line[size.x] != '\0'; size.x++) {
            if (line[size.x] == '#') {
                galaxies[n++] = (Point){size.x,size.y};
            }
        }

        size.y++;
    }

    // Expand
    for (size_t x = 0; x < size.x; x++) {
        bool has_galaxy = false;

        for (size_t i = 0; i < n; i++) {
            if (galaxies[i].x == x) {
                has_galaxy = true;
                break;
            }
        }

        if (has_galaxy) continue;
        size.x += expansion;

        for (size_t i = 0; i < n; i++) {
            if (galaxies[i].x < x) continue;

            galaxies[i].x += expansion;
            
        }

        x += expansion; // skip newly created space 
    }

    for (size_t y = 0; y < size.y; y++) {
        bool has_galaxy = false;

        for (int i = 0; i < n; i++) {
            if (galaxies[i].y == y) {
                has_galaxy = true;
                break;
            }
        }

        if (has_galaxy) continue;
        size.y += expansion;

        for (int i = 0; i < n; i++) {
            if (galaxies[i].y < y) continue;

            galaxies[i].y += expansion;
            
        }

        y += expansion; // skip newly created space 
    }

    size_t total_distance = 0;
    for (int i = 0; i < n; i++) {
        for (size_t j = i+1; j < n; j++) {
            Point a = galaxies[i];
            Point b = galaxies[j];

            total_distance += distance(a, b);
        }
    }

    printf("%zu\n", total_distance);

    return 0;
}

void draw_universe(Point galaxies[], int n, Point size) {
    for (size_t y = 0; y < size.y; y++) {
        for (size_t x = 0; x < size.x; x++) {
            bool has_galaxy = false;

            for (size_t i = 0; i < n; i++) {
                if (galaxies[i].x == x && galaxies[i].y == y) {
                    has_galaxy = true;
                    break;
                }
            }

            if (has_galaxy) printf("#");
            else printf(".");
        }

        printf("\n");
    }
}

size_t distance(Point a, Point b) {
    return (a.x > b.x ? a.x - b.x : b.x - a.x) + (a.y > b.y ? a.y - b.y : b.y - a.y);
}
