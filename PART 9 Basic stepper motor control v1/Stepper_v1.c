/*
 * File:   main.c
 * Author: john m holmes
 *
 * Created on 09 March 2023, 15:37
 * 
 * programmed using a Pickit 3
 * MAPLAB version 5.50 XC8 version 2.36
 * 
 * This is used to control a 28BYJ-48 5V Stepper Motor ULN2003 Driver Module
 * 
 * RCO goes to Pin 1 on the driver unit
 * RC1 goes to Pin 2 
 * RC2 goes to Pin 3
 * RC3 goes to pin 4
 * 
 * A button is connected to Pin 4 and this controls the direction of the stepper motor
 * 
 * When programming this it is advised not to have the power going to the ULN2003 if you are
 * using the PIckit 3 to supply 4.75 volts for the PIC
 * 
 * Once programmed you can remove the Pickit 3 and provide 5 volts separately
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
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)


#include <xc.h>

#define _XTAL_FREQ 4000000  

#define sw RA3                         // PIN 4 has a button attached to it.

void main(void) {
    
    ANSEL = 0x00;                      // All PORTS are digital
    TRISA = 0x00;                      // All PORT A are outputs unless changed later in code
    TRISC = 0X00;                      // All PORT C are outputs
    PORTA = 0X00;                      // All PORT A are set to LOW
    PORTC = 0X00;                      // All PORT A are set to LOW
    
    signed char step = 0;              // starts the switch case at 0 on startup
            
    while(1){                          // start the forever loop
        
        switch(step){
            case 0: PORTC = 1; break;  // = 0001 RC0 HIGH
            case 1: PORTC = 9; break;  // = 1001 RC0 , RC3 HIGH 
            case 2: PORTC = 8; break;  // = 1000 RC3 HIGH
            case 3: PORTC = 12; break; // = 1100 RC2 , RC3 HIGH
            case 4: PORTC = 4; break;  // = 0100 RC2 HIGH
            case 5: PORTC = 6; break;  // = 0110 RC1 , RC2 HIGH
            case 6: PORTC = 2; break;  // = 0010 RC1 HIGH
            case 7: PORTC = 3; break;  // = 0011 RC0 , RC1 HIGH
            
        }
        
        if(RA3 == 1)                   // First check to see if the button has been pressed 1 means it is not pressed.
            _delay(2);                 /* Used for a de-bounce for the button press notice we have set this to 2 instruction cycles
                                         by using the _delay() macro if we go to large it will slow the stepper motor down in 
                                        a clockwise direction.*/
            if(RA3 == 1)step ++;       // increases the case value by 1 rotation of stepper motor is clockwise.
        else step --;                  // decreases the case value by 1 rotation of stepper motor is anti clockwise.
        
        if(step > 7) step = 0;         // once the case is above 7 it resets it back to 0 allowing it to loop.
        
        if(step < 0) step = 7;         // once the case is below 0 it resets it back to 7 allowing it to loop.
        
        __delay_ms(1);                 /* used for the speed of the stepper motor can be increased  by making the delay value larger 
                                         1 is the fastest speed we can drive this steeper motor at.*/
                
    }
    
}
