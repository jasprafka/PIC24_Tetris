/*
 * File:   PIC24_setup.c
 * Author: Jacob
 *
 * Created on November 23, 2020, 2:37 PM
 */


#include "xc.h"
#include "PIC24_setup.h"




/**
 * NAME:_T1Interrupt
 * PARAMETERS: n/a
 * PURPOSE: Timer 1 interrupt that turns off Timer 1 and clears its flag
 * RETURNS: n/a
 */

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {
    _TON = 0;
    _T1IF = 0;
    TMR1 = 0;
}

/**
 * NAME: initPIC
 * PARAMETERS: n/s
 * PURPOSE: Initialize the PIC24 to function with the NHD-C12864LZ-FSW-FBW-3V3 
 * and four buttons. This includes setting up 8 pins as an 8-bit parallel data bus
 * and setting up 4 pins with pull-up resistors in order to scan for presses for 
 * each of the four buttons. This also sets up Timer 1 at a 1:64 prescale and 
 * enables the Timer 1 interrupt at priority level 4.
 * RETURNS: n/a
 */

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
