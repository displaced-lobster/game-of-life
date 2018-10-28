#include "Cell.h"

unsigned int Cell::cell_width = 0;
unsigned int Cell::cell_height = 0;

void Cell::draw(UTFT *GLCD) {
        int x1 = x * cell_width;
        int x2 = x1 + cell_width;
        int y1 = y * cell_height;
        int y2 = y1 + cell_height;

        GLCD->fillRect(x1, y1, x2, y2);
}

bool Cell::death_condition(int neighbors) {
        return (neighbors < 2 || neighbors > 3);
}

void Cell::kill(UTFT *GLCD) {
        alive = false;
        to_kill = false;
        GLCD->setColor(VGA_BLACK);
        draw(GLCD);
        GLCD->setColor(VGA_WHITE);
}

void Cell::birth(UTFT *GLCD) {
        alive = true;
        to_birth = false;
        draw(GLCD);
}

bool Cell::birth_condition(int neighbors) {
        return neighbors == 3;
}
