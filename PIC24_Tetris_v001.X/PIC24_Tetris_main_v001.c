/*
 * File:   PIC24_Tetris_main_v001.c
 * Author(s): Jacob Sprafka
 *
 * Created on October 23, 2020, 7:08 PM
 */

// CW1: FLASH CONFIGURATION WORD 1 (see PIC24 Family Reference Manual 24.1)
#pragma config ICS = PGx1          // Comm Channel Select
#pragma config FWDTEN = OFF        // Watchdog Timer is disabled
#pragma config GWRP = OFF          // Writes to program memory are allowed
#pragma config GCP = OFF           // Code protection is disabled
#pragma config JTAGEN = OFF        // JTAG port is disabled


// CW2: FLASH CONFIGURATION WORD 2 (see PIC24 Family Reference Manual 24.1)
#pragma config I2C1SEL = PRI       // Use default SCL1/SDA1 pins
#pragma config IOL1WAY = OFF       // IOLOCK may be changed via unlocking seq
#pragma config OSCIOFNC = ON       // CLKO/RC15 functions as I/O pin
#pragma config FCKSM = CSECME      // Clock switching is enabled, Fail-Safe Clock Monitor is enabled
#pragma config FNOSC = FRCPLL      // Fast RC Oscillator with PLL module (FRCPLL)

#include "xc.h"
#include "PIC24_setup.h"
#include "spraf_Lab5_LCD.h"

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {
    _TON = 0;
    _T1IF = 0;
    TMR1 = 0;
}

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

int main(void) {

    _T1IE = 1;

    //Setup
    initPIC();

    PR1 = 25000;
    _T1IF = 0;
    _T1IP = 4;
    T1CON = 0x20;




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
//  command(0xA2);         //LCD drive voltage bias ratio.  
//  command(0xA0);         //Ram->SEG output = normal
//  command(0xC8);         //COM direction scan = normal (0xC8 in Example Initialization Program) 
//  command(0xA4);         //Display All Points normally..
//  command(0x40);         //Display Start Line
//  command(0x25);         //Resistor Ratio Set 
//  command(0x81);         //Electronic Volume Command (set contrast) Double Byte: 1 of 2
//  command(0x10);         //Electronic Volume value (contrast value) Double Byte: 2 of 2 
//  command(0x2F);         //Power Control Set
//  command(0xAF);         //Display ON


    //Main game loop
    while (1) {

    }

    return 0;
}
