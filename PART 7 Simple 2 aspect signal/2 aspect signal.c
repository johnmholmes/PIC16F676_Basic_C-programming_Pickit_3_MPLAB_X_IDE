/*
 * File:   main.c
 * Author: johnm
 *
 * Created on 27 February 2023, 14:50
 * 
 * PIC16F676 Programmed using MPLAB X IDE version 5.5 and XC8 version 2.36
 * 
 * This code is going to read the state of PIN RA5 change a 2 aspect signal to red from green,
 * RC0 will have a red connected to it with a 330 ohm resistor to ground.
 * RC1 will be a green LED connected to a 330 ohm resistor to ground
 * RA5 will have a switched connected to ground and use a weak internal pull up resistor on the PIC
 * For this I have set a 15 second delay from being triggered this could be set longer if required.
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

#define _XTAL_FREQ 4000000      //Setup the onboard oscillation at 4mhz
#define Green_led RC1           //Setup green led on PIN 9 RC1
#define Red_led RC0             //Setup red led on PIN 10 RC0

void main(void) {
    
    ANSEL = 0X00;               //All pins set to digital
    TRISC = 0X00;               //All port C set s outputs
    TRISA = 0X00;               //All port a set as outputs until overridden
    PORTC = 0X00;               //All pot c set to low at startup
       
    PORTAbits.RA5 = 1;          //Pin RA5 set as an input
    
    
    OPTION_REGbits.nRAPU = 0;   //PORTA pull-ups are enabled by individual PORT latch values "nRAPU = 0;"
    WPUAbits.WPUA5 = 1;         //Pin RA5 has its pull enabled holding pin at 5 volts    
    Green_led = 1;              //Turn on the green led at startup
    Red_led = 0;                //Turn off the red led at startup
    
    //Start the main loop program
    while(1){
        if (PORTAbits.RA5 == 0){ //Reads the state of the push button in this case if grounded 
        Red_led = 1;             //Turn on the red led
        Green_led = 0;           //Turn off the green led
        __delay_ms(5000);        //Wait 5 seconds
        Green_led = 1;           //Turn on the green led
        Red_led = 0;             //Turn off the red led and return to check the button state
        }
    }


}
