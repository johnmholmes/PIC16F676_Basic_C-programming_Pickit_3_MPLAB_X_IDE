/*
 * File:   main.c
 * Author: dan1138
 * Modified John Holmes
 * Target: PIC16F676
 * Compiler: XC8 v2.36
 * IDE: MPLABX v6.00
 *
 * Created on March 21, 2023, 12:22 PM
 * 
 *                              PIC16F676
 *                    +------------:_:------------+
 *           5V  -> 1 : VDD                   VSS : 14 <- GND
 *               <> 2 : RA5/T1CKI     PGD/AN0/RA0 : 13 <- PGD
 *               <> 3 : RA4/AN3       PGC/AN1/RA1 : 12 <- PGC
 *           VPP -> 4 : RA3/VPP       int/AN2/RA2 : 11 <> 
 *               <> 5 : RC5/CPP1          AN4/RC0 : 10 <> in1
 *               <> 6 : RC4/C2OUT         AN5/RC1 : 9  <> in2
 *           in4 <> 7 : RC3/AN7           AN6 RC2 : 8  <> in3
 *                    +---------------------------:
 *                               DIP-14
 * 
 */
/*
 * Initialize the target specific configuration bits
 */
#pragma config FOSC = INTRCIO
#pragma config WDTE = OFF
#pragma config PWRTE = OFF
#pragma config MCLRE = ON 
#pragma config BOREN = OFF
#pragma config CP = OFF
#pragma config CPD = OFF
/*
 * Include target specific definitions
 */
#include <xc.h>
/* define the system clock frequency that this code will setup */
#define _XTAL_FREQ (4000000ul) /* The "ul" suffix stands for "unsigned long" and indicates to the compiler 
                                * that the constant value should be treated as an unsigned long integer. 
                                * This is important when dealing with microcontrollers and other embedded systems 
                                * that require precise timing and frequency control.
                                * 4000000 is just below the limits but for faster chips you will need to use (ul). */
                                

// Initialize this PIC for the hardware target.
 
void Init_PIC(void)
{   
    INTCON = 0;           /* turn off interrupts */
    PIE1   = 0;           /* turn of Peripheral interrupts */
    
    CMCON = 0x07;         /* turn off comparators */
    VRCON = 0x00;         /* VOLTAGE REFERENCE CONTROL REGISTER set to 0 */

    ADCON1 = 0x10;        /* set FOSC/8 as ADC clock source */
    ADCON0 = 0x80;        /* Right justified, External VREF, select channel 0 and turn off ADC 0xC0 */
    ANSEL  = 0x03;        /* set RA0,RA1 as analogue inputs, all others as digital */
    ADCON0bits.ADON = 1;  /* A/D converter module is operating */
    ADCON0bits.GO_nDONE = 1;  /* A/D conversion cycle in progress. Setting this bit starts an A/D conversion cycle.
                               * This bit is automatically cleared by hardware when the A/D conversion has completed. */
    
    __delay_ms(500);      /* wait for ICD before making PGC and PGD outputs */

    
    OPTION_REG = 0x51;    /* Select FOSC/4 as clock source for TIMER0 and 1:4 prescaler, enable pull-ups on PORTA */
    WPUA = 0x3C;          /* Turn off weak pull-ups on RA0,RA1 00111100 */
    TRISA = 0xFF;         /* Set PORTA RA0,RA1,RA2,RA4,RA5 as inputs */
    TRISC = 0x30;         /* Set PORTC RC0,RC1,RC2,RC3 as outputs */
    PORTC = 0;            /* turn off drivers to stepper motor */
    
    /*
     * TIMER0 is setup to clock from FOSC/4 with a 1:4 prescaler. The timer will assert
     * an overflow event every (prescaler * count length). The TIMER0 count length is fixed 
     * at 256 counts, so the event is asserted every 1024 clocks. This is 1.024 milliseconds
     * based on a 4MHz system clock.
     */
}
/*
 * Interrupt handlers this has no code to be called in the function but we use the interrupt timer for
 * the delay timing.
 */
void __interrupt() ISR_Handler(void)
{
}
/*
 * Step motor 28 BYJ-48 & ULN2003 stepper motor driver
 * 
 * 
 *  Sequence to Rotate in clockwise direction using half steps at the Pic output
 * +------------+-----------------------------------------------+
 * :   Motor    :                     Step                      :
 * +   Wire     :-----+-----+-----+-----+-----+-----+-----+-----+
 * :   Colour   :  1  :  2  :  3  :  4  :  5  :  6  :  7  :  8  :
 * +------------+-----+-----+-----+-----+-----+-----+-----+-----+
 * : Orange RC0 : 5 V : 5 V : off : off : off : off : off : 5 V :
 * : Yellow RC1 : off : 5 V : 5 V : 5 V : off : off : off : off :
 * : Pink   RC2 : off : off : off : 5 V : 5 V : 5 V : off : off :
 * : Blue   RC3 : off : off : off : off : off : 5 V : 5 V : 5 V :
  * +------------+-----+-----+-----+-----+-----+-----+-----+-----+
 */

// Inputs: Count, 16-bit signed integer, Positive values set clockwise, negative counterclockwise.
//          Wait, 8-bit unsigned integer, Number of TIMER0 events to wait until next step.
void StepMotor(int16_t Count, uint8_t Wait)
{
    static uint8_t state = 0;   /* static variable state, 8-bit unsigned integer available inside function call */
    /*  values for HalfSteps             0001, 0011, 0010, 0110, 0100, 1100, 1000, 1001 */
    static const uint8_t HalfSteps[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09};
    uint8_t delay;

    do
    {
        if (Count > 0)                  /* Check if Count is greater than 0 if so then continue through the next line of code. */
        {
            PORTC = HalfSteps[state];   /* drive stepper to select state */
            state--;                    /* step one state clockwise */
            state &= 0x07;              /* This is a bitwise operation that performs a bitwise AND between the variable
                                         * "state" and the hexadecimal value "0x07". In binary, "0x07" 
                                         * is represented as "00000111",  
                                         * which means that this operation will only keep the three least significant bits
                                         * of the "state" variable and set all other bits to zero. */
            Count--;                    /* update step count by - 1 */
        }
        else if (Count < 0)             /* Check if Count is less than 0 if so then continue through the next line of code. */
        {
            PORTC = HalfSteps[state];   /* drive stepper to select state */ 
            state++;                    /* step one state counterclockwise */ 
            state &= 0x07;              /* This is a bitwise operation that performs a bitwise AND between the variable 
                                         * "state" and the hexadecimal value "0x07". In binary, "0x07" 
                                         * is represented as "00000111", 
                                         * which means that this operation will only keep the three least significant bits
                                         * of the "state" variable and set all other bits to zero. */ 
            Count++;                    /* update step count by + 1 */ 
        }
        /* Wait between steps */
        if(Wait > 0)                    /* Check if Wait is greater than 0 if so then continue through the next line of code. */
        {
            delay = Wait;               /* delay takes the value of wait */
            do {
               while(INTCONbits.T0IF == 0) {
               }                        /* Wait for the interrupt flag to be set as 1 */
               INTCONbits.T0IF = 0;     /* Reset the interrupt flag to 0 */
               delay = delay -1;        /* delay is decremented by one. */
            } while (delay > 0);        /* loop until the delay reaches zero */
        }
    } while (Count != 0);               /* Loop will continue to execute as long as the value of the variable "Count" 
                                         * is not equal to zero. */
}
/*
 * Main application
 */
void main(void) 
{
    /*
     * Application initialization
     */
    Init_PIC();                        /* Calls the function void Init_PIC(void) to setup the Pic */
    /*
     * Application process loop
     */
    while(1)                    /* Loop forever */
    {
        StepMotor(4076, 4);     /* step about 1 revolution clockwise at 4.096 milliseconds per step */
        __delay_ms(1000);       /* Delay 1000 ms or 1 second */
        StepMotor(-2038, 2);    /* step about 1/2 a revolution counterclockwise at 2.048 milliseconds per step  */
        __delay_ms(1000);       /* Delay 1000 ms or 1 second */
        StepMotor(-2038, 2);    /* step about 1/2 a revolution counterclockwise at 2.048 milliseconds per step  */
        __delay_ms(1000);       /* Delay 1000 ms or 1 second */ 
    }
}