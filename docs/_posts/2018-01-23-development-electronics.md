---
layout: default
categories: development
title: "Electronics"
order: 4
---

We did an initial prototype device with a Wemos D1 Mini and found that all the components worked together well. We quickly decided that we wanted to try to make our own breakout board for the ESP8266. This has a number of benefits including making wiring easier and fitting the form factor of our housing better with less compromises.

I designed and milled the first circuitboard based on a schematic from Craig and the ESP8266 wiki.

Unfortutaly I than had many problems uploading to the ESP8266
### Problems uploading to the ESP2866

After milling a circuit board breakout for an ESP8266-12F and soldering it all together I discovered that I couldn't upload to it at all. It would run the code and appear to go into Uart Bootloader Mode but would not receive any code at all.

This is the schematic of the circuit board.
![Circuit Board 1]({{site.imageurl}}/circuitboard - 1(doesnotwork).png)
**THIS CIRCUIT DOES NOT WORK BTW**

I than breadboarded out the same circuit on a breadboard and ran the following tests using different Resistor values.

#### This doesn't work:
CH_PD   - Pulled High (10k Resistor) - think this needs to be 1k
GPIO 15 - Pulled Low (10k Resistor)
GPIO 02 - Floating
GPIO 00 - Pulled Low (1k Resistor)
Fails to connect most times, sometime connects but failed half way through upload

#### This doesn't work:
CH_PD   - Pulled High (1k Resistor)
GPIO 15 - Pulled Low (1k Resistor)
GPIO 02 - Floating
GPIO 00 - Connected to GND (via jumper)
Fails to connect to ESP2866

#### This works:
CH_PD   - Pulled High (1k Resistor)
GPIO 15 - Pulled Low (1k Resistor)
GPIO 02 - Floating
GPIO 00 - Pulled Low (1k Resistor)

#### This works + allows for easy switching between programming and boot:
CH_PD   - Pulled High (1k Resistor)
GPIO 15 - Pulled Low (1k Resistor)
GPIO 02 - Floating
GPIO 00 - Pulled Low (1k Resistor with switch) + Pulled High (10k Resistor)

I than swapped out the resistors on the circuit board AND... it still didn't work,
After trying a different esp and that also not working I milled an updated circuit board.

After soldering the new board together with the correct resistors, I was finally able to upload the code.

This is the final circuit board design.
It has breakout headers for 2 i2c connections, an addressable led header, a speaker header and an FDTI connector for uploading code.
![Circuit Board 2]({{site.imageurl}}/ciruictboard - 2.png)

### Breakout board for capacitive touch Sensor

Due to the capacitive touch breakout board that I bought being really large. I wanted to make my own board in a smaller form factor.

After designing a small formfactor breakout board for the ttp229 capactive touch chip, I cut it and soldered the components to it AND.... nothing happened.
I could not get anything out of the chip, and after trying for a day I made the call to move on to more important things. If I have spare time before the end of this project I will try to revisit this as it would be really useful.
