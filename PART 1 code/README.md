# PIC16F676_Basic_C programming_Pickit_3_MPLAB_X_IDE

In part 1 of my journey was to learn how to connect up the Pic16F676 to the Pickit 3 Since making the video I have been advised to add a 100nF capacitor across the 5 volt line and the ground line so Pins 1 and 14 of the chip. This is to smooth out any noise on the supply and also any noise caused by the operation of the General input output pins (GPIO).

https://youtu.be/O7069OKVfkY

The datasheet is freely available from the Microchip website but also look for the Errita incase there has been any updates since the chip was manufactured.

http://ww1.microchip.com/downloads/en/devicedoc/40039f.pdf

You will have to search for the Errita on there main website.

https://www.microchip.com/en-us/product/PIC16F676

Attention to the wiring diagram is important to make sure you use the 10k resistor to hold Pin 4 at 5 volts when programming.
