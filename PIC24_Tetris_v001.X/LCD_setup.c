/*
 * File:   LCD_setup.c
 * Author: Jacob
 *
 * Created on November 25, 2020, 3:02 PM
 */


#include "xc.h"
#include "LCD_setup.h"



void lcdCmd(int cmd) {
    LATB = 0XFFFF;
    LATB &= cmd;
    _LATB10 = 0; //LATB10 = A0
    _LATB11 = 0; //LATB11 = RW
    _LATB8 = 0; //LATB8 = CS
    _LATB12 = 1; //LATB12 = E
    _LATB12 = 0; //LATB12 = E
    _LATB8 = 1; //LATB8 = CS
    _LATB11 = 1; //LATB11 = RW

}

void lcdData(int data) {
    LATB = 0XFFFF;
    LATB &= data;
    _LATB10 = 1; //LATB10 = A0
    _LATB11 = 0; //LATB11 = RW
    _LATB8 = 0; //LATB8 = CS
    _LATB12 = 1; //LATB12 = E
    _LATB12 = 0; //LATB12 = E
    _LATB8 = 1; //LATB8 = CS
    _LATB11 = 1; //LATB11 = RW
}

void initLCD(void) {
    _LATB9 = 0;
    _TON = 1;
    while (!_T1IF);

    _LATB9 = 1; //LATB9 = RES
    _TON = 1;
    while (!_T1IF);

    _LATB8 = 1; //LATB8 = CS
    _LATB12 = 1; //LATB12 = E
    _LATB11 = 1; //LATB11 = RW
    _LATB10 = 1; //LATB10 = A0

    lcdCmd(0xffa2);
    lcdCmd(0xffa0);
    lcdCmd(0xffc8);
    lcdCmd(0xffa4);
    lcdCmd(0xff40);
    lcdCmd(0xff25);
    lcdCmd(0xff81);
    lcdCmd(0xff10);
    lcdCmd(0xff2f);
    lcdCmd(0xffaf);
}

void clearLCD(void){
    unsigned int i, j;
    unsigned int page = 0xffB0;
    lcdCmd(0xff40); //Display start address + 0x40
    for (i = 0; i < 8; i++) { //64pixel display / 8 pixels per page = 8 pages
        lcdCmd(page); //send page address
        lcdCmd(0xff10); //column address upper 4 bits + 0x10
        lcdCmd(0xff00); //column address lower 4 bits + 0x00
        for (j = 0; j < 128; j++) { //128 columns wide
            lcdData(0xff00); //send picture data
            
        }
        page++; //after 128 columns, go to next page
    }
}
