#include <stdio.h>
#include <stdlib.h>

#define ROLLING 'O'
#define CUBE '#'
#define EMPTY '.'

#define ENTITY_BUFFER 8192

typedef struct point {
    size_t x, y;
} Point;

typedef struct entity {
    char type;
    Point pos;
} Entity;

typedef struct EntityList {
    size_t length;
    Entity list[ENTITY_BUFFER];
} EntityList;

void push_entity(EntityList* this, Entity e) {
    this->list[this->length++] = e;
}

void draw(EntityList rocks, Point size) {
    for (int y = 0; y < size.y; y++) {
        for (int x = 0; x < size.x; x++) {
            int has_rock = 0;
            for (int i = 0; i < rocks.length; i++) {
                Entity e = rocks.list[i];
                if (e.pos.x == x && e.pos.y == y) {
                    printf("%c", e.type);
                    has_rock = 1;
                    break;
                }
            }

            if (!has_rock) printf(".");
        }

        printf("\n");
    }
}

int main() {
    size_t bufsize = 128;
    char* line = malloc(bufsize);

    EntityList rocks;
    Point canva = {0,0};
    while (getline(&line, &bufsize, stdin) > 0) {
        for (canva.x = 0; line[canva.x] != '\n'; canva.x++) {
            if (line[canva.x] == CUBE || line[canva.x] == ROLLING) {
                Entity e = {line[canva.x], canva};

                if (e.type == ROLLING) {
                    Point target = {e.pos.x, 0};
                    for (int j = 0; j < rocks.length; j++) {
                        Point rockp = rocks.list[j].pos;
                        if (rockp.x == target.x && rockp.y < e.pos.y && rockp.y >= target.y) {
                            target.y = rockp.y + 1;
                        }
                    }

                    e.pos = target;
                }

                push_entity(&rocks, e);
            }
        }

        canva.y++;
    }

    printf("%zux%zu\n",canva.x,canva.y);
    draw(rocks, canva);

    size_t sum = 0;
    for (int i = 0; i < rocks.length; i++) {
        if (rocks.list[i].type != ROLLING) continue;
        sum += canva.y - rocks.list[i].pos.y;
    }

    printf("%zu\n", sum);
}
