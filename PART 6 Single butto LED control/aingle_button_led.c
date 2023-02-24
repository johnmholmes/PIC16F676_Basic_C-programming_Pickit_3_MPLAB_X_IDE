/*
 * File:   main.c
 * Author: johnm
 *
 * Created on 24 February 2023, 07:50
 * 
 * PIC16F676 Programmed using MPLAB X IDE version 5.5 and XC8 version 2.36
 * 
 * This code is going to read the state of PIN RA5 and will set pin RC0 as the same state,
 * RC0 will have a LED connected to it with a 330 ohm resistor to ground.
 * RA% will have a switched connected to ground and use a weak internal pull up resistor on the PIC
 */
// PIC16F676 Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = INTRCIO   // Oscillator Selection bits (INTOSC oscillator: I/O function on RA4/OSC2/CLKOUT pin, I/O function on RA5/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RA3/MCLR pin function select (RA3/MCLR pin function is digital I/O, MCLR internally tied to VDD)
#pragma config BOREN = OFF      // Brown-out Detect Enable bit (BOD disabled)
#pragma config CP = OFF         // Code Protection bit (Program Memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)

#include <xc.h>

void main(void) {
    
    ANSEL = 0X00;               //All pins set to digital
    TRISC = 0X00;               //All port C set s outputs
    TRISA = 0X00;               //All port a set as outputs until overridden
    PORTC = 0X00;               //All pot c set to low at startup
    
    
    
    
    
    PORTAbits.RA5 = 1;          //Pin RA5 set as an input
    
    
    OPTION_REGbits.nRAPU = 0;   //All port a global set to allow weak pulls
    WPUAbits.WPUA5 = 1;         //Pin RA5 has its pull enabled holding pin at 5 volts    
    
    while(1){
        PORTCbits.RC0 = PORTAbits.RA5;  //Because the RA5 pin is HIGH the LED will be on until the button is pressed
    }
    


}
