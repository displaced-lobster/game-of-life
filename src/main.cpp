#include "Arduino.h"

#include <string.h>
#include <UTFT.h>
#include <URTouch.h>

#include "Cell.h"
#include "Grid.h"

#define GENERATION_LIMIT 250

// Fonts
extern uint8_t BigFont[]; // 16 x 16

// Objects
UTFT myGLCD(SSD1289, 38, 39, 40, 41);
int generation = 0;

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
        myGLCD.setBrightness(10);

        display_screen_size();
        delay(5000);
        myGLCD.clrScr();

        grid.width = GRID_WIDTH;
        grid.height = GRID_HEIGHT;

        Cell::cell_width = myGLCD.getDisplayXSize() / grid.width;
        Cell::cell_height = myGLCD.getDisplayYSize() / grid.height;

        grid.initialise(&myGLCD);
}

void loop() {
        if (generation == GENERATION_LIMIT) {
                grid.initialise(&myGLCD);
                generation = 0;
        }

        delay(250);

        for (unsigned int y = 0; y < grid.height - 1; y++) {
                for (unsigned int x = 0; x < grid.width; x++) {
                        Cell *cell = &grid.cells[y][x];
                        int neighbors = grid.neighbor_count(cell);
                        if (cell->alive && cell->death_condition(neighbors)) {
                                cell->to_kill = true;
                        } else if (!cell->alive && cell->birth_condition(neighbors)) {
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
