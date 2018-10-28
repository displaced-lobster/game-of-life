#ifndef GRID
#define GRID

#include <UTFT.h>

#include "Cell.h"

#define GRID_WIDTH 32
#define GRID_HEIGHT 24

class Grid {
        public:
                unsigned int width;
                unsigned int height;

                Cell cells[GRID_HEIGHT][GRID_WIDTH];

                void initialise(UTFT *GLCD);

                int neighbor_count(Cell *cell);

                unsigned char average_r(Cell *cell);
                unsigned char average_g(Cell *cell);
                unsigned char average_b(Cell *cell);
};

#endif
