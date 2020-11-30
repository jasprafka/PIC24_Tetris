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


void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {
    _TON = 0;
    _T1IF = 0;
    TMR1 = 0;
}

//Initialize the PIC24
void initPIC() {
    _RCDIV = 0; //Set Fcy = 16Mhz
    AD1PCFG = 0x9FFF; //Set all pins to digital I/O
    TRISB = 0x0; //Set PORTB to outputs
    TRISA = 0xFF; //Set LATA to inputs
    _CN2PUE = 1; //Enable Pull-up on RA0
    _CN3PUE = 1; //Enable Pull-up on RA1
    _CN30PUE = 1; //Enable Pull-up on RA2
    _CN29PUE = 1; //Enable Pull-up on RA3

    PR1 = 25000;
    _T1IF = 0;
    _T1IP = 4;
    _T1IE = 1;
    T1CON = 0x20;
}
