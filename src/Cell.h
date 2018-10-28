#ifndef CELL
#define CELL

#include <UTFT.h>

class Grid;

class Cell {
        public:
                static unsigned int cell_width;
                static unsigned int cell_height;

                unsigned int x;
                unsigned int y;

                unsigned char r;
                unsigned char g;
                unsigned char b;

                bool alive;
                bool to_kill;
                bool to_birth;

                void draw(UTFT *GLCD);
                void kill(UTFT *GLCD);
                void birth(UTFT *GLCD);
                void set_color(unsigned char new_r, unsigned char new_g, unsigned char new_b);

                bool death_condition(int neighbors);
                bool birth_condition(int neighbors);
};

#endif
