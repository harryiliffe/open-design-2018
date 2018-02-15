---
layout: default
categories: assembly
title: "Electronics"
order: 4
---

This section will guide you through assembling the Electronics.
### Step 1: Purchase Components.

For this project there are a number of components, some are required, other are optional.

1. Main Circuit Board
  * ESP8266 - The main brains of Greg
  * 10k ohm resistors x 2 (1206 package size)
  * 1k ohm resistors x 3 (1206 package size)
  * 100 ohm resistor x 1 (Optional: For Speaker, 1206 package size)
  * 100nF capacitor (Recommended, used for extra stability, 1206 package size)
  * 3.3v Regulator (Must be rated for +500mAh, We used 	[AMS1117](http://www.advanced-monolithic.com/pdf/ds1117.pdf))
  * Slide switch (To toggle flashing mode on the ESP8266)
  * Tactile Switch (3mm x 6mm form factor)
  * Circuit Board (You can order one using the included Gerber File or mill your own.)

   Many of these items are included in the fab inventory therefore are stocked at most fab labs.
   Find your closest one on [fablab.io](https://www.fablabs.io/)

2. Addressable LEDS

   We used a small strip of WS2812B LEDs.

3. Capacitive Touch Module

   We used a [16 Keys Capacitive touch TTP229 I2C module](https://robotdyn.com/catalog/modules/16-keys-capacitive-touch-ttp229-i2c-module.html) but you could also use a [Adafruit 12-Key Capacitive Touch Sensor Breakout - MPR121](https://www.adafruit.com/product/1982)

4. MPU 6050 (GY-521) (Optional)

5. Speaker (Optional)

   Any 8 ohm speaker will do, as long as it is small enough to fit in the housing.

6. Conductive Thread

   This is used link Greg's fins and legs to the capacitive touch sensor.

7. Battery

   We used a 3.7v 250mAh lipo battery.

 8. FTDI Cable

    For programming the ESP8266.

### Step 2: Fabricate Circuit Board.

If you do not want to make your own circuit board, you can use an ESP8266 breakout board such as a [Wemos D1 Mini](https://wiki.wemos.cc/products:d1:d1_mini)

1. Find the circuit files in the [eagle folder of our git](https://github.com/harryiliffe/open-design-2018/tree/master/eagle)

2. Produce the circuit board using your chosen fabrication method.

   We used [fabmodules.org](http://fabmodules.org/) and an mdx-20.

3. Solder the components onto the circuit board.
  * Remember not to make the ESP8266 too hot.

### Step 3: Connect Everything

### Step 4: Test Components

Using the test code available in [code/tests](https://github.com/harryiliffe/open-design-2018/tree/master/code/test) to test each component in turn.
Once you can confirm that each component works move on to [Software](/open-design-2018//assembly-software/).
