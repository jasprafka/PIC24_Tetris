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
#include "LCD_setup.h"
#include "tetris_pieces.h"

int main(void) {

    //Setup
    initPIC();
    initLCD();
    clearLCD();

    //Variables
    unsigned int screen[1024];
    
    curTetromino playPiece;
    unsigned int tetro[128] = {
        0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, //P1, Col 0-15
        0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, //P1, Col 16-32
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, //P2, Col 0-15
        0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, //P2, Col 16-32
        0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, 0xffff, //P3, Col 0-15
        0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, //P3, Col 16-32
        0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, //P4, Col 0-15
        0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, 0xff00, //P4, Col 16-32
    };
    playPiece.tetromino = tetro;

    //Timer one setup
    //Deprecated, may or may not still be necessary
    PR1 = 35000;
    _T1IF = 0;
    _T1IP = 4;
    _T1IE = 1;
    T1CON = 0x30;


    //Main game loop
    while (1) {

//        drawTetromino(playPiece, screen);
//        drawNHDLogo();

        drawScreenBuf(screen);
    }

    return 0;
}
