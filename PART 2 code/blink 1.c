/*
 * File:   blink 1.c
 * Author: johnm
 *
 * Created on 18 February 2023, 10:07
 */

// PIC16F676 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = ON       // RA3/MCLR pin function select (RA3/MCLR pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)



#include <xc.h>
#define _XTAL_FREQ 4000000
#define LED1 RC0             //Sets up the led on pin 10 / RC0 and we can us LED1 in the code


void main(void) {
    ANSEL = 0x00;
    //ANSEL = 0b00000000;
    //ANSELbits.ANS0 = 0;         //Sets All pins are digital pins 
    TRISC = 0X00;                 //Sets all PORTC as outputs C0 To C5
    //TRISC = 0b000000;
    //TRISCbits.TRISC0 = 0;
    PORTC = 0XFF;                 //Sets all PORTC to low on startup
    //PORTC =0b111110;

while(1){                     //Tell the code to loop for ever (1) means TRUE
    LED1 = 0;                 //Turns off led 
    __delay_ms(200);          //This set the time delay. ** this value will have a upper limit depending on the chip seems 25 seconds max
    LED1 = 1;                 //Turns on led 
    __delay_ms(200);          //delays again
}                             //Program never gets out of the loop so goes back to just after while(1))    
}