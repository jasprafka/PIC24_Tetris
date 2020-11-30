/*
 * File:   LCD_setup.c
 * Author: Jacob
 *
 * Created on November 25, 2020, 3:02 PM
 */


#include "xc.h"
#include "LCD_setup.h"

void LCD_cmd(char com) {
    LATB = com; //LATB<7:0>
    _LATB8 = 0;
    
}

void LCD_data(char data) {

}

void initLCD(void) {

}
