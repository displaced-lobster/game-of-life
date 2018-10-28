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
                                cell->draw(GLCD);
                        } else {
                                cell->alive = false;
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
