# Part 10 Controlling the number of steps and the direction as well as the speed of the stepper motor.

This program is based on Dans code with extra details and different moves. This came about due to a post I made on the Micrcochip forum and mentioning what I was hoping to do. His code has been developed with other Items since.

----------------
# Inportant changes since making the video

At time code 4:42:

Line 57, ADCON0 = 0x80; is described as to how it affect the Analog to Digital Converter.

What you say about this statement is what the comment on in the source code says. This is a problem as the comment, /* Right justified, External VREF, select channel 0 and turn off ADC */ is not correct. The correct comment is: /* Right justified, VREF is VDD, select channel 0 and turn off ADC */

At time code 5:44:

Line 63, __delay_ms(500); is described. The description is accurate but does not explain why this delay is present.

Because the code that Microchip provides to control device programming tools like the PICkit3 is kind of crap it lets the user application run for a bit. When this happens on a PIC16F676 and the controller sets the GPIO lines used for PGD and PGC to outputs too soon the attempt to program the target device could fail and leave the controller bricked in a way that can be hard to recover.

To make this problem less likely a delay of 500 milliseconds after a device reset is helpful.

At time code 8:00:

A description of the interrupt handler function begins.


The description is somewhat misleading and TIMER0 is mentioned in this context. This is misleading because this application does not enable any interrupts. At present this function is a placeholder for implementation of future functionality.

-------------
# Basic information

This is a C code for a stepper motor driver, specifically for driving a bipolar stepper motor. The code is written for the PIC16F676 microcontroller and was compiled using the XC8 compiler.

The code initializes the PIC16F676, sets up the configuration bits, and defines the system clock frequency using the _XTAL_FREQ macro. It then defines an interrupt handler, but the function is empty, so the interrupt is not used.

The main function initializes the stepper motor driver by setting the input and output pins for the PIC microcontroller, and then it waits for 500 milliseconds before proceeding. The stepper motor is driven using a sequence of half-steps, and the sequence is defined in the comments in the code.

Overall, this code is a basic stepper motor driver for a bipolar stepper motor. The code could be modified for different stepper motors by adjusting the sequence of half-steps. The code could also be modified to include additional features, such as acceleration and deceleration, to provide more precise control over the stepper motor.

I have felt it is worth showing as it had some interesting lessons to be learn.

----------------------------------------------------------------------------------------------------------------------------------------------------------

This includes using Arrays and bitwise operators.

In C programming language, an array is a collection of elements of the same data type, which are stored in a block of memory. Each element in the array is accessed by its index, which starts at 0 for the first element and goes up to the size of the array minus one.

In the code you can see the Array being used to control the stepper motor rotation pulses.

values for HalfSteps---------------- 0001, 0011, 0010, 0110, 0100, 1100, 1000, 1001 

static const uint8_t HalfSteps[8] = {0x01, 0x03, 0x02, 0x06, 0x04, 0x0C, 0x08, 0x09};

We have given a variable name for the Array as HalfSteps.

In C programming language, static and const are both keywords used to specify the properties of a variable.

The keyword static in C is used to declare a variable that retains its value even after the function exits. In other words, the variable's value persists throughout the program's execution.

The keyword const in C is used to declare a variable whose value cannot be modified after initialization. This means that the value assigned to a const variable remains constant throughout the program's execution. Any attempt to modify the value of a const variable will result in a compile-time error.

In this example, HalfSteps is a constant variable of type uint8_t (unsigned 8-bit integer), declared with both static and const keywords. The values of this variable is set to 0x01, etc and it cannot be modified during the program's execution.

The [8] tells the compiler the Array will have 8 elements within it.

Then inside the {brackets} you will see a series of hexadecimal values. These represent the binary state of the PORTC output pins.

Example 0x01 requires the PIC to set PORTC0 as 1 so at 5 volts and PORTC1-3 as 0 so 0 volts.

The PORTC has 6 available outputs however earlier in the setup we set all the PORTC as state 0 so we do not need to worry about the bits 4 & 5.

One thing to remember if we wanted to call one of the values in the Array the first element is [0] and not [1].

------------------------------------------------------------------------------------------------------------------

# Bitwise operator usage within the code.

state &= 0x07;

a bitwise operation that performs a bitwise AND between the variable "state" and the hexadecimal value "0x07".

In binary, "0x07" is represented as "00000111", which means that this operation will only keep the three least significant bits of the "state" variable and set all other bits to zero.

Therefore, this operation is commonly used to mask or clear out the upper bits of a variable, ensuring that only the lower bits hold relevant information.

this keeps the state within HalfSteps table this is bitwise and modulo, so we have 8 step in the array so once we hit 8 we have 8 MOD 8 =0 and -1 MOD 8 = 7
