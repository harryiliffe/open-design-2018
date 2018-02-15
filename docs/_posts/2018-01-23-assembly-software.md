---
layout: default
categories: assembly
title: "Software"
order: 4
---

This section will guide you through assembling the Electronics.
### Step 1: Install Requirements.
There are a number of software requirements you need to be able to program Greg.
1. [Install Arduino](https://www.arduino.cc/en/Main/Software)
2. Download [ESP8266 boards](https://github.com/esp8266/Arduino) + [Arduino ESP8266 filesystem uploader](https://github.com/esp8266/arduino-esp8266fs-plugin)
3. Download required libraries
  * [FastLed](http://fastled.io/) - for led control
  * [i<sup>2</sup>cdevlib](https://www.i2cdevlib.com/) - for mpu6050 lib
  * [ArduinoJson](https://github.com/bblanchon/ArduinoJson) - for config storage
  * [arduinoWebSockets](https://github.com/Links2004/arduinoWebSockets) - for hosting the companion app

4. Setup Flashing Tools
  * Board: GENRIC ESP8266 MODULE
  * Flash Mode: DIO
  * Flash Size: 4M(1M SPIFFS)

   or select the board you have chosen.
5. Open Arduino IDE and connect Greg's brain to your computer via an FTDI Cable.

   IMAGE OF FDTI CABLE CONNECTION
6. Download the [main code](https://github.com/harryiliffe/open-design-2018/tree/master/code/main)
  * Open main.ino in Arduino

7. Upload the data folder.
* Download the [companion app](https://github.com/harryiliffe/open-design-2018/tree/master/companionapp) and place it in the code folder "main" in a folder named "data".
* Click the ESP8266 SKETCH DATA Upload

8. Upload the sketch


## Troubleshooting

TODO: ADD TROUBLESHOOTING
