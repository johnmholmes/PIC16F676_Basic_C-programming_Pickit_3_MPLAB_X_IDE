/*
 * File:   main.c
 * Author: john holmes
 * Disclaimer
 * This code has been written for and tested on the following PIC16F676 only
 * Part of the code may work on other chips but do so at your own risk
 * There are 6 leds which are red on RC0, Amber on RC1 and green on RC2 the all have a 330 ohm resistor in series 
 * with each led
 * The internal frequency is set to 4mhz 
 * 
 * This is not the only way this could be done but is for demonstration purposes only.
 *
 * Created on 19 March 2022, 19:08
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


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>

#define _XTAL_FREQ 4000000     // Frequency setting for the PIC
#define LONG_TIME  8000       //Maxium delay time 30 seconds for this picj  
#define MEDIUM_TIME 4000       //19 seconds is a good setting
#define SHORT_TIME 2000        //3 seconds is a good setting


/*In this function we need to set bank 1 Red to on and bank 2 amber on only.
 *So this is bit 0 and bit 4 & 5 remember the bit 0 is the most right one.
 *We then set a delay for these to be a short delay of 3 seconds
 */
void red_RedAmberLed(){
    // bit    543210
    //        RAGGAR
    PORTC = 0b110001;
    __delay_ms(SHORT_TIME);
}

/*In this function we need to set bank 1 Red to on and bank 2 Green on only.
 *So this is bit 0 and bit 4  remember the bit 0 is the most right one.
 *We then set a delay for these to be a short delay of 19 seconds
 */
void red_Green(){
    // bit    543210
    //        RAGGAR
    PORTC = 0b001001;
    __delay_ms(MEDIUM_TIME);   
}

/*In this function we need to set bank 1 Red to on and bank 2 Green on only.
 *So this is bit 0 and bit 5  remember the bit 0 is the most right one.
 *We then set a delay for these to be a short delay of 3 seconds
 */
void red_Amber(){
    // bit    543210
    //        RAGGAR
    PORTC = 0b010001;
    __delay_ms(SHORT_TIME);      
    
}

/*In this function we need to set bank 1 Red and Amber to on and bank 2 Red on only.
 *So this is bits 0,1,and bit 5  remember the bit 0 is the most right one.
 *We then set a delay for these to be a short delay of 3 seconds
 */
void redAmber_Red(){
    // bit    543210
    //        RAGGAR
    PORTC = 0b100011;
    __delay_ms(SHORT_TIME);      
    
}

/*In this function we need to set bank 1 Red  to on and bank 2 Green on only.
 *So this is bit 2 and bit 5  remember the bit 0 is the most right one.
 *We then set a delay for these to be a short delay of 25 seconds
 */
void green_Red(){
    // bit    543210
    //        RAGGAR
    PORTC = 0b100100;
    __delay_ms(LONG_TIME);     
    
}

/*In this function we need to set bank 1 Red  to on and bank 2 Green on only.
 *So this is bit 1 and bit 5  remember the bit 0 is the most right one.
 *We then set a delay for these to be a short delay of 3 seconds
 */
void amber_Red(){
    // bit    543210
    //        RAGGAR
    PORTC = 0b100010;
    __delay_ms(SHORT_TIME);      
    
}
      


void main(void) {
    ANSEL = 0b00000000;
    TRISA = 0X00;
    TRISC = 0x00;             //Port C is set to  all outputs. 
    PORTC = 0x00;             //Sets all LED's off (1 = on)
    __delay_ms(5000);


while(1)                  //loop forever
    {
    red_RedAmberLed();    //First function call once that function completes it will return to the next line.
    red_Green();
    red_Amber();
    redAmber_Red();
    green_Red();        
    amber_Red();          //Once this function finishes it will go back to the start of the while loop.    

    
    }                 // The code never gets out of the loop so goes back to the first PORTD call
    

}