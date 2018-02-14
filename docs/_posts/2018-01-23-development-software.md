---
layout: default
categories: development
title: "Software"
order: 4
---
## Problems uploading to the ESP2866

After milling a circuit board breakout for an ESP8266-12F and soldering it all together I discovered that I couldn't upload to it at all. It would run the code and appear to go into Uart Bootloader Mode but would not receive any code at all.

This is the schematic of the circuit board.
![Circuit Board 1]({{site.imageurl}}/circuitboard - 1(doesnotwork).jpg)
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

After soldering this board together with the correct resistors, I was finally able to upload the code.

This is the final circuit board design.
It has breakout headers for 2 i2c connections, an addressable led header, a speaker header and an FDTI connector for uploading code.
![Circuit Board 2]({{site.imageurl}}/ciruictboard - 2.jpg)
