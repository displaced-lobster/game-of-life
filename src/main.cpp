#include "Arduino.h"

//#include "Cell.h"
//#include "Grid.h"
#include <string.h>
#include <UTFT.h>
#include <URTouch.h>


#define GRID_WIDTH 32
#define GRID_HEIGHT 24

#define GENERATION_LIMIT 250

// Fonts
extern uint8_t BigFont[]; // 16 x 16

// Objects
UTFT myGLCD(SSD1289, 38, 39, 40, 41);
int generation = 0;

class Grid;

class Cell {
        public:
                static unsigned int cell_width;
                static unsigned int cell_height;
                unsigned int x;
                unsigned int y;
                bool alive;
                bool to_kill;
                bool to_birth;

                void draw(UTFT *GLCD);
                void kill(UTFT *GLCD);
                void birth(UTFT *GLCD);
                int neighbor_count(Grid *grid);
                bool death_condition(Grid *grid);
                bool birth_condition(Grid *grid);
};

class Grid {
        public:
                unsigned int width;
                unsigned int height;
                Cell cells[GRID_HEIGHT][GRID_WIDTH];

                void initialise();
                int translate_x(int x);
                int translate_y(int y);
};

void Cell::draw(UTFT *GLCD) {
        int x1 = x * cell_width;
        int x2 = x1 + cell_width;
        int y1 = y * cell_height;
        int y2 = y1 + cell_height;

        GLCD->fillRect(x1, y1, x2, y2);
}

int Cell::neighbor_count(Grid *grid) {
        int neighbors = 0;

        unsigned int grid_y = (y > 0) ? y - 1 : 0;
        for ( ; grid_y < y + 2 && grid_y < grid->height - 1; grid_y++) {
                unsigned int grid_x = (x > 0) ? x - 1 : 0;
                for ( ; grid_x < x + 2 && grid_x < grid->width; grid_x++) {
                        //Cell *cell = &((*grid).cells[grid_y][grid_x]);

                        if(grid_x == x && grid_y == y) {
                                continue;
                        }

                        if (grid->cells[grid_y][grid_x].alive) {
                                neighbors++;
                        }
                }
        }

        return neighbors;
}

bool Cell::death_condition(Grid *grid) {
        int neighbors = neighbor_count(grid);
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

bool Cell::birth_condition(Grid *grid) {
        return neighbor_count(grid) == 3;
}

void Grid::initialise() {
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
                                cell->draw(&myGLCD);
                        } else {
                                cell->alive = false;
                        }
                }
        }
}

unsigned int Cell::cell_width = 0;
unsigned int Cell::cell_height = 0;
Grid grid;

void display_screen_size() {
        char screen_size[8];
        char width[4];
        char height[4];

        int screen_height = myGLCD.getDisplayYSize();

        String width_str = String(myGLCD.getDisplayXSize());
        String height_str = String(screen_height);

        width_str.toCharArray(width, 4);
        height_str.toCharArray(height, 4);

        strcpy(screen_size, width);
        strcat(screen_size, "x");
        strcat(screen_size, height);

        myGLCD.print(screen_size, CENTER, screen_height / 2);
}

void setup() {
        myGLCD.InitLCD();
        myGLCD.clrScr();
        myGLCD.fillScr(VGA_BLACK);
        myGLCD.setColor(VGA_WHITE);
        myGLCD.setFont(BigFont);

        display_screen_size();
        delay(5000);
        myGLCD.clrScr();

        grid.width = GRID_WIDTH;
        grid.height = GRID_HEIGHT;

        Cell::cell_width = myGLCD.getDisplayXSize() / grid.width;
        Cell::cell_height = myGLCD.getDisplayYSize() / grid.height;

        grid.initialise();
}

void loop() {
        if (generation == GENERATION_LIMIT) {
                grid.initialise();
                generation = 0;
        }

        delay(250);

        for (unsigned int y = 0; y < grid.height - 1; y++) {
                for (unsigned int x = 0; x < grid.width; x++) {
                        Cell *cell = &grid.cells[y][x];

                        if (cell->alive && cell->death_condition(&grid)) {
                                cell->to_kill = true;
                        } else if (!cell->alive && cell->birth_condition(&grid)) {
                                cell->to_birth = true;
                        }
                }
        }

        for (unsigned int y = 0; y < grid.height - 1; y++) {
                for (unsigned int x = 0; x < grid.width; x++) {
                        Cell *cell = &grid.cells[y][x];

                        if (cell->to_kill) {
                                cell->kill(&myGLCD);
                        } else if (cell->to_birth) {
                                cell->birth(&myGLCD);
                        }
                }
        }

        generation++;
}
