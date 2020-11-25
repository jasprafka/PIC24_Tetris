/*
 * File:   PIC24_setup.c
 * Author: Jacob
 *
 * Created on November 23, 2020, 2:37 PM
 */


#include "xc.h"
#include "PIC24_setup.h"


/*
 * TO-DO:
 * 
 */


//IC1 ISR

void __attribute__((interrupt, auto_psv)) _IC1Interrupt(void) {
    /*
     * TO-DO:
     * Handle button input
     */

    _IC1IF = 0;
    
    if(PORTA != 0xf){
        LATB = 0b111100000;
    }
    


    int i, j;
    for (i = 0; i < 1000; i++) {
        int j;
        for (j = 0; j < 1000; j++) {
        }
    }


    
}

//T3 ISR

void __attribute__((interrupt, auto_psv)) _T3Interrupt(void) {
    _T3IF = 0;
}

//Initialize the PIC24

void initPIC() {
    _RCDIV = 0; //Set Fcy = 16Mhz
    AD1PCFG = 0x9FFF; //Set all pins to digital I/O
    TRISB = 0x8000; //Set PORTB to outputs, set PORTB15 to input
    TRISA = 0xFF; //Set LATA to inputs
    _CN2PUE = 1; //Enable Pull-up on RA0
    _CN3PUE = 1; //Enable Pull-up on RA1
    _CN30PUE = 1; //Enable Pull-up on RA2
    _CN29PUE = 1; //Enable Pull-up on RA3
}

//Initialize Input Capture (IC) for the 4 buttons

void initIC1(void) {

    //Pin remapping
    __builtin_write_OSCCONL(OSCCON & 0xBF); //Unlock Registers
    _IC1R = 15; //Set IC1 to RP15
    __builtin_write_OSCCONL(OSCCON | 0x40); //Lock Registers

    IC1CON = 1; //Set IC1 to capture every edge and capture from Timer 3

    //Configure interrupts for IC1
    _IC1IF = 0;
    _IC1IP = 4;
    _IC1IE = 1;

}

//Initialize Timer 3

void initTimer3(void) {
    PR3 = 32000;
    T3CON = 0x8000;
}