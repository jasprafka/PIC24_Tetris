/*
 * File:   tetris_pieces.c
 * Author: Jacob
 *
 * Created on December 3, 2020, 4:01 PM
 */


#include "xc.h"
#include "sprite.h"
#include "LCD_setup.h"

/**
 * NAME: drawSprite
 * PARAMETERS: sprite tet - a data type created by us to make it easier to track
 *  the position and rotation of the tetris piece currently being played 
 *  unsigned char screen[1024]- array of pixel data to draw to the screen
 * PURPOSE: takes the sprite that is passed in and draws it in the correct 
 *  position and orientation on the screen
 * RETURNS: n/a
 */

void drawSprite(sprite tet, unsigned char screen[1024]) {
    unsigned int px, py;
    for (px = 0; px < 32; px++) {
        for (py = 0; py < 4; py++) {
            if (tet.image[py * 32 + px] != 0x00) {
                screen[(py + tet.yPos)* 128 + (tet.xPos + px)] = tet.image[(py * 32) + px];
            }
        }
    }
}

/**
 * NAME: collide
 * PARAMETERS: sprite tet - the tetris piece currently being manipulated by the player
 *  unsigned char pField[1024] - the array of pixel data so we can check the area 
 *  surrounding the tetris piece for possible collisions caused by movement
 *  char dir - a character that indicates the direction that player had wanted 
 *  the piece to move
 * PURPOSE: takes the direction that the player wants to move the piece and 
 *  checks if it is doable or not. If the move is doable, the function will 
 *  return 1. If it is not doable, it will return 0
 * RETURNS: an int which indicates whether or not the desired tetris piece 
 *  movement is possible or not
 */

int collide(sprite tet, unsigned char pField[1024], char dir) {

    int px, py, pi, fi;

    for (px = 0; px < 32; px++)
        for (py = 0; py < 4; py++) {

            pi = py * 32 + px;

            if (tet.image[pi] == 0xff) {
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
                            tet.image -= 384;
                        } else {
                            tet.image += 128;
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