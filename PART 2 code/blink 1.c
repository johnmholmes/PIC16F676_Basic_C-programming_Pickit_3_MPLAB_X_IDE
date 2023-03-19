/*
 * File:   blink 1.c
 * Author: John Holmes
 *
 * Created on 18 February 2023, 10:07
 */

/*                             PIC16F676
 *                    +------------:_:------------+
 *           5V  -> 1 : VDD                   VSS : 14 <- GND
 *               <> 2 : RA5/T1CKI     PGD/AN0/RA0 : 13 <- PGD
 *               <> 3 : RA4/AN3       PGC/AN1/RA1 : 12 <- PGC
 *           VPP -> 4 : RA3/VPP       int/AN2/RA2 : 11 <> 
 *               <> 5 : RC5/CPP1          AN4/RC0 : 10 <> LED1
 *               <> 6 : RC4/C2OUT         AN5/RC1 : 9  <>  
 *               <> 7 : RC3/AN7           AN6 RC2 : 8  <>  
 *                    +---------------------------:
 *                               DIP-14
 * 
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
#define LED1 RC0                //Sets up the led on pin 10 / RC0 and we can us LED1 in the code


void main(void) {
    ANSEL = 0x00;              //Sets All pins are digital pins 
    //ANSEL = 0b00000000;      //Alternative way to set it
    //ANSELbits.ANS0 = 0;      //Alternative way to set it       
    TRISC = 0X00;              //Sets all PORTC as outputs C0 To C5
    //TRISC = 0b000000;        //Alternative way to set it 
    //TRISCbits.TRISC0 = 0;    //Alternative way to set it 
    PORTC = 0XFF;              //Sets all PORTC to low on startup
    //PORTC =0b111110;         //Alternative way to set it 

while(1){                      //Tell the code to loop for ever (1) means TRUE
    LED1 = 0;                  //Turns off led 
    __delay_ms(200);           //This set the time delay. ** this value will have a upper limit depending on the chip seems 25 seconds max
    LED1 = 1;                  //Turns on led 
    __delay_ms(200);           //delays again
}                              //Program never gets out of the loop so goes back to just after while(1))    
}
