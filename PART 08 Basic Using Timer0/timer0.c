/*
 * File:   main.c
 * Author: john holmes
 *
 * Created on 07 March 2023, 16:33
 * 
 * MPLAB version 5.50 XC8 version 2.36
 * 
 * This code is to have 3 LEDS flashing at 3 different rates and uses TIMER0 of the PIC16F676 to control the
 * timing. The LEDS are fitted to PIN 8, 9 , and 10 of the PIC PIN 11 is used for the TIMER0
 */


// PIC16F676 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config MCLRE = OFF      // RA3/MCLR pin function select (RA3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = ON       // Brown-out Detect Enable bit (BOD enabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF   

#include <xc.h>
#define _XTAL_FREQ 4000000      // set the interrnal clock to 4 MHZ


int usec = 0;                   // First led timer set to 0
int useca = 0;                  // Second led timer set to 0
int usecb = 0;                  // Third led timer set to 0

void __interrupt BLINK()
{
    TMR0 = 8;                   // The timer roles over at 255 we require 256-6 + 2 to give us 250 microseconds
    INTCONbits.T0IF=0;          // Resets the interrupt flog to 0
    usec++;                     // increment the usec variable by 1 with every timer0 Roll over
    useca++;                    // increment the useca variable by 1 with every timer0 Roll over
    usecb++;                    // increment the usecb variable by 1 with every timer0 Roll over
    
    /* The first if statement is waiting for the timer to reach 4000 and then it will toggle the LED on RC0 to the 
       opposite state and then it resets the counter back to 0 for the next loop
       This Led will flash at a 1 second frequency Maths  1000000 microseconds/250 microseconds = 4000 */
    
    if(usec>=4000){
        RC0 = ! RC0;
        usec=0;   }

    /* The first if statement is waiting for the timer to reach 2000 and then it will toggle the LED on RC0 to the 
       opposite state and then it resets the counter back to 0 for the next loop
       This Led will flash at 0.5 seconds frequency */
            
    if(useca>=2000){
        RC1 =! RC1;
        useca = 0;
                   }
    /* The first if statement is waiting for the timer to reach 1000 and then it will toggle the LED on RC0 to the 
       opposite state and then it resets the counter back to 0 for the next loop
       This Led will flash at 0.25 seconds frequency */
    
    if(usecb>=1000){
        RC2 = ! RC2;
        usecb=0;   }
    
  }
    
 void main(void) {
    ANSEL=0x00;                 // All Analogue pins set to digital pins
    TRISA=0x00;                 // PORTS A set to outputs
    TRISC=0x00;                 // PORTS C set to outputs
    PORTA=0x00;                 // PORTS A set to off
    PORTC=0x00;                 // PORTS C set to off
    
    INTCONbits.GIE = 1;         // 1 = Enables all unmasked interrupts
    INTCONbits.T0IF = 0;        // 0 = TMR0 register did not overflow
    INTCONbits.T0IE = 1;        // 1 = Enables the TMR0 interrupt
    OPTION_REGbits.T0CS = 0;    // 0 = Internal instruction cycle clock (CLKOUT)
    OPTION_REGbits.PSA = 1;     // 1 = PAS preset scaler set to the WDT (Watch dog timer)
    OPTION_REGbits.PS0 = 1;     // The PS0,1,and 2 have been set to 1's which for the WDT is 1:128
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS2 = 1;
    
    
    while(1);
 }   
