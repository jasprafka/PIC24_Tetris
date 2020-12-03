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
    unsigned int i, j;

}

void drawScreenBuf(unsigned int screen[1024]) {
    unsigned int i, j, count = 0;
    unsigned int page = 0xffB0;
    lcdCmd(0xff40); //Display start address + 0x40
    for (i = 0; i < 8; i++) { //64pixel display / 8 pixels per page = 8 pages
        lcdCmd(page); //send page address
        lcdCmd(0xff10); //column address upper 4 bits + 0x10
        lcdCmd(0xff00); //column address lower 4 bits + 0x00
        for (j = 0; j < 128; j++) { //128 columns wide
            lcdData(screen[count] | 0xff00); //send picture data
            count++;
        }
        page++; //after 128 columns, go to next page
    }
}

//    unsigned int i, j, count = 0;
//    unsigned int page = 0xffB0;
//    lcdCmd(0xff40); //Display start address + 0x40
//    for (i = 0; i < 8; i++) { //64pixel display / 8 pixels per page = 8 pages
//        lcdCmd(page); //send page address
//        lcdCmd(0xff10); //column address upper 4 bits + 0x10
//        lcdCmd(0xff00); //column address lower 4 bits + 0x00
//        for (j = 0; j < 128; j++) { //128 columns wide
//            lcdData(NHD_Logo[count] | 0xff00); //send picture data
//            count++;
//        }
//        page++; //after 128 columns, go to next page
//    }