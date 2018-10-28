#include "Grid.h"

void Grid::initialise(UTFT *GLCD) {
        for (unsigned int y = 0; y < height - 1; y++) {
                for (unsigned int x = 0; x < width; x++) {
                        Cell *cell = &cells[y][x];

                        randomSeed(analogRead(0));
                        int rand = random(2);

                        cell->y = y;
                        cell->x = x;
                        cell->to_kill = false;
                        cell->to_birth = false;

                        if (rand) {
                                cell->alive = true;
                                cell->r = random(100, 256);
                                cell->g = random(100, 256);
                                cell->b = random(100, 256);
                                cell->draw(GLCD);
                        } else {
                                cell->alive = false;
                                cell->r = 0;
                                cell->g = 0;
                                cell->b = 0;
                        }
                }
        }
}

int Grid::neighbor_count(Cell *cell) {
        int neighbors = 0;

        unsigned int y = (cell->y > 0) ? cell->y - 1 : 0;

        for  ( ; y < cell->y + 2 && y < height - 1; y++) {
                unsigned int x = (cell->x > 0) ? cell->x - 1 : 0;

                for ( ; x < cell->x + 2 && x < width; x++) {
                        if (x == cell->x && y == cell->y) {
                                continue;
                        }

                        if (cells[y][x].alive) {
                                neighbors++;
                        }
                }
        }

        return neighbors;
}

unsigned char Grid::average_r(Cell *cell) {
        unsigned int y = (cell->y > 0) ? cell->y - 1 : 0;

        for  ( ; y < cell->y + 2 && y < height - 1; y++) {
                unsigned int x = (cell->x > 0) ? cell->x - 1 : 0;

                for ( ; x < cell->x + 2 && x < width; x++) {
                        if (x == cell->x && y == cell->y) {
                                continue;
                        }

                        if (cells[y][x].alive) {
                                return cells[y][x].r;
                        }
                }
        }

        return 0;
}
unsigned char Grid::average_g(Cell *cell) {
        unsigned int y = (cell->y > 0) ? cell->y - 1 : 0;

        for  ( ; y < cell->y + 2 && y < height - 1; y++) {
                unsigned int x = (cell->x > 0) ? cell->x - 1 : 0;

                for ( ; x < cell->x + 2 && x < width; x++) {
                        if (x == cell->x && y == cell->y) {
                                continue;
                        }

                        if (cells[y][x].alive) {
                                return cells[y][x].g;
                        }
                }
        }

        return 0;
}
unsigned char Grid::average_b(Cell *cell) {
        unsigned int y = (cell->y > 0) ? cell->y - 1 : 0;

        for  ( ; y < cell->y + 2 && y < height - 1; y++) {
                unsigned int x = (cell->x > 0) ? cell->x - 1 : 0;

                for ( ; x < cell->x + 2 && x < width; x++) {
                        if (x == cell->x && y == cell->y) {
                                continue;
                        }

                        if (cells[y][x].alive) {
                                return cells[y][x].b;
                        }
                }
        }

        return 0;
}
