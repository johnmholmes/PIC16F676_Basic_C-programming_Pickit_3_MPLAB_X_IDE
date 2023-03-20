# Part 1 Of The Journey.

In part 1 of my journey was to learn how to connect up the Pic16F676 to the Pickit 3 Since making the video I have been advised to add a 100nF capacitor across the 5 volt line and the ground line so Pins 1 and 14 of the chip. This is to smooth out any noise on the supply and also any noise caused by the operation of the General input output pins (GPIO).

This video shows the setup I use less the capacitor mentioned
https://youtu.be/O7069OKVfkY

The datasheet is freely available from the Microchip website but also look for the errata in case there has been any updates since the chip was manufactured.

http://ww1.microchip.com/downloads/en/devicedoc/40039f.pdf

You will have to search for the Errita on there main website.

https://www.microchip.com/en-us/product/PIC16F676

Also I would advise you take a look at the XC8 compilier guide available from this link

https://ww1.microchip.com/downloads/en/devicedoc/50002053g.pdf

This has given me a good insight into a few things I have been struggling with in the past.

Attention to the wiring diagram is important to make sure you use the 10k resistor to hold Pin 4 at 5 volts when programming.

You will need to decide if you are going to supply the 5 volts from the Pickit 3 or from a seaerate supply. If you use the Pickit 3 you will need to set that up in the project preferences. This will be explained in the next video.

Issues and comments welcome.
