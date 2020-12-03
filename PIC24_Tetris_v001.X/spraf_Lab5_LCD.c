/*
 * File:   spraf_Lab5_LCD.c
 * Author: Jacob Sprafka
 *
 * Created on November 1, 2020, 9:34 AM
 */


#include "xc.h"
#include "spraf_Lab5_LCD.h"


#define _SEN2 I2C2CONbits.SEN 
#define _PEN2 I2C2CONbits.PEN
#define RETHOME 0b00000010
#define SHIFTCR 0b00010101
#define WRTSLV 0b01111100

void __attribute__((interrupt, auto_psv)) _T1Interrupt(void) {
    _TON = 0;
    _T1IF = 0;
    TMR1 = 0;
}

//Where a period of 50000 = 200ms

void startTMR1(int period) {
    PR1 = period;
    _T1IF = 0;
    _T1IP = 4;
    T1CON = 0x8020;
}

void PIC_init(void) {
    _RCDIV = 0; //Set RCDIV=1:1 (default 2:1) Fcy = 16Mhz
    AD1PCFG = 0x9fff; //sets all pins to digital I/O
}

void I2C2_init(void) {
    I2C2CONbits.I2CEN = 0;
    _MI2C2IF = 0;
    I2C2BRG = 0x9D;
    I2C2CONbits.I2CEN = 1;
}

void lcd_cmd(char package) {
    _SEN2 = 1; //Initiate start condition
    while (_SEN2); //Wait for start bit to complete
    _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF

    I2C2TRN = WRTSLV; // 8-bits consisting of the slave address and the R/nW bit
    while (!_MI2C2IF);
    _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF

    I2C2TRN = 0b00000000; // 8-bits consisting of control byte
    while (!_MI2C2IF);
    _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF

    I2C2TRN = package; // 8-bits consisting of the data byte
    while (!_MI2C2IF);
    _PEN2 = 1;
    while (_PEN2);

}

void lcd_init(void) {
    startTMR1(12500);
    while (!_T1IF);
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00111001); // function set, extended instruction mode
    lcd_cmd(0b00010100); // interval osc
    lcd_cmd(0b01110000); // contrast C3-C0
    lcd_cmd(0b01011110); // Ion, Bon, C5-C4
    lcd_cmd(0b01101100); // follower control
    startTMR1(50010);
    while (!_T1IF);
    lcd_cmd(0b00111000); // function set, normal instruction mode
    lcd_cmd(0b00001100); // Display On
    lcd_cmd(0b00000001); // Clear Display
    startTMR1(5000);
    while (!_T1IF);

}

//Where 0 <= x <= 39
//Where y = 0 or 1

void lcd_setCursor(char x, char y) {
    int pos = (40 * y) + x;
    int i;
    lcd_cmd(RETHOME);
    for (i = 0; i < pos; i++) {
        lcd_cmd(SHIFTCR);
    }

}

void lcd_printChar(char data) {
    
    _SEN2 = 1; //Initiate start condition
    while (_SEN2); //Wait for start bit to complete
    _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF

    I2C2TRN = 0b01111100; // 8-bits consisting of the slave address and the R/nW bit
    while (!_MI2C2IF);
    _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF

    I2C2TRN = 0b01000000; // 8-bits consisting of control byte
    while (!_MI2C2IF);
    _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF

    I2C2TRN = data; // 8-bits consisting of the data byte
    while (!_MI2C2IF);
    _PEN2 = 1; //Stop bit
    while (_PEN2);
}

void lcd_printStr(char str[], size_t size){
    
    _SEN2 = 1; //Initiate start condition
    while (_SEN2); //Wait for start bit to complete
    _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF

    I2C2TRN = WRTSLV; // 8-bits consisting of the slave address and the R/nW bit
    while (!_MI2C2IF);
    _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF
    
    int i;
    for (i = 0; i < size - 2; i++) {
        I2C2TRN = 0b11000000; // 8-bits consisting of control byte
        while (!_MI2C2IF);
        _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF

        I2C2TRN = str[i]; // 8-bits consisting of the data byte
        while (!_MI2C2IF);
        _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF
        
    }

    
    I2C2TRN = 0b01000000; // 8-bits consisting of control byte
    while (!_MI2C2IF);
    _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF

    I2C2TRN = str[size - 2]; // 8-bits consisting of the data byte
    while (!_MI2C2IF);
    _MI2C2IF = 0; //Clear IFS3bits.MI2C2IF
    
    
    _PEN2 = 1; //Stop bit
    while (_PEN2);

}