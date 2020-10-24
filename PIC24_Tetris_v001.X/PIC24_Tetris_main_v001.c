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

int main(void) {
    return 0;
}
