/*
 * File:   tetris_pieces.c
 * Author: Jacob
 *
 * Created on December 3, 2020, 4:01 PM
 */


#include "xc.h"
#include "tetris_pieces.h"
#include "LCD_setup.h"

void drawTetromino(curTetromino tet, unsigned int screen[1024]) {
    unsigned int px, py;
    for (px = 0; px < 32; px++) {
        for (py = 0; py < 4; py++) {
            if (tet.tetromino[py * 32 + px] != 0xff00) {
                if (tet.tetromino[(py * 32) + px] != 0xff00) {
                    screen[(py + tet.yPos)* 128 + (tet.xPos + px)] = tet.tetromino[(py * 32) + px];
                }
            }
        }
    }
}
