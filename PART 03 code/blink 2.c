/*
 * File:   mainc.c
 * Author: johnm
 *
 * Created on 19 February 2023, 12:15
 */
// PIC16F676 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA3/MCLR pin function select (RA3/MCLR pin function is MCLR)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 4000000
#define LED1 RC0                //Sets up the led on pin 10 / RC0 and we can us LED1 in the code
#define LED2 RC1                //Sets up the led on pin 9 / RC1 and we can us LED2 in the code

void main(void) {
    //ANSEL = 0X00; 
    ANSEL = 0b01000001;
    TRISA = 0X00;
    TRISC = 0X00;
    PORTA = 0X00;
    PORTC = 0X00;
    
    while(1){
        LED1 = 0;               //Turns off led 1
        LED2 = 1;               //Turns on led  2
        __delaywdt_ms(100);   
        LED1 = 1;               //Turns on led 1
        LED2 = 0;               //Turns off led 2
        __delay_ms(100);   
    }
            
    
}