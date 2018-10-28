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
};

#endif
