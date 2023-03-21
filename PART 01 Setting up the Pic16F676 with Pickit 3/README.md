# Part 1 Of The Journey.

In part 1 of my journey was to learn how to connect up the Pic16F676 to the Pickit 3. Since making the video I have Added a 100nF capacitor across the 5V and GND pins (pins 1 and 14) of the PIC16F676 microcontroller.

When a microcontroller switches its GPIO pins on and off, it can cause spikes or dips in the voltage supply, known as noise. This noise can potentially affect the performance of the microcontroller and any connected devices.

By adding a capacitor across the power supply and ground pins, the capacitor acts as a filter to smooth out any noise on the power supply. This helps to ensure that the microcontroller and any connected devices receive a stable and clean power supply.

Additionally, the capacitor can also help reduce noise caused by the operation of the GPIO pins. As the microcontroller switches its GPIO pins, any changes in the current draw can cause fluctuations in the voltage supply. The capacitor can help to absorb these fluctuations and prevent them from affecting the performance of the microcontroller and connected devices.

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
