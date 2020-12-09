/*
 * File:   tetris_pieces.c
 * Author: Jacob
 *
 * Created on December 3, 2020, 4:01 PM
 */


#include "xc.h"
#include "tetris_pieces.h"
#include "LCD_setup.h"

void drawTetromino(curTetromino tet, unsigned char screen[1024]) {
    unsigned int px, py;
    for (px = 0; px < 32; px++) {
        for (py = 0; py < 4; py++) {
            if (tet.tetromino[py * 32 + px] != 0x00) {
                screen[(py + tet.yPos)* 128 + (tet.xPos + px)] = tet.tetromino[(py * 32) + px];
            }
        }
    }
}

int collide(curTetromino tet, unsigned char pField[1024], char dir) {

    int px, py, pi, fi;

    for (px = 0; px < 32; px++)
        for (py = 0; py < 4; py++) {

            pi = py * 32 + px;

            if (tet.tetromino[pi] == 0xff) {
                switch (dir) {
                    case 0:
                        fi = (tet.yPos + py + 1) * 128 + (tet.xPos + px);
                        if (pField[fi] != 0) {
                            return 0;
                        }
                        break;
                    case 1:
                        fi = (tet.yPos + py - 1) * 128 + (tet.xPos + px);
                        if (pField[fi] != 0) {
                            return 0;
                        }
                        break;
                    case 2:
                        fi = (tet.yPos + py) * 128 + (tet.xPos + px + 1);
                        if (pField[fi] != 0) {
                            return 0;
                        }
                        break;
                    case 3:
                        if (tet.rotation == 3) {
                            tet.tetromino -= 384;
                        } else {
                            tet.tetromino += 128;
                        }
                        if (pField[(tet.yPos + py + 1) * 128 + (tet.xPos + px)] != 0 || pField[(tet.yPos + py) * 128 + (tet.xPos + px)] != 0) {
                            return 0;
                        }
                        break;
                }
            }
        }


    return 1;
}