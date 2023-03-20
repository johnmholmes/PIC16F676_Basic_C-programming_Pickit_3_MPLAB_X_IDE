# Part 10 Conrolling the number of steps and the  direction as well as the speed of the motor.

This program is based on Dans code with extra details and different moves. This came about due to a post I made on the Micrcochip forum and mentioning what I was hoping to do. His code has been developed with other Items since.

I have felt it is worth showing as it had some interesting lessons to be learn.

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
