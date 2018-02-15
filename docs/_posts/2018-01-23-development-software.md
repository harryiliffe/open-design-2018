---
layout: default
categories: development
title: "Software"
order: 4
---

I wanted to keep the code easy to understand and edit, so I decided to use the Arduino IDE.
I started my coding in the first mode, IDLE mode (a mode which shows emotions). This mode was really easy to make as I just took the capacitive touch input and made an onStroke() function.

Next I coded in a number of different modes for the apps.

We decided on a few apps:
* Idle/Emotive mode
* Hide & Seek
* Gyroscopic mode

These modes would be the base functionality of Greg, with the plan to add more if we have more time.

Next I expanded the functionality immensely. I added fading leds, sound, a way to change modes, support for remembering configurations and easy gyroscope integration. All in 1 night.

Next we added support for the companion app. This involved using the ESP8266 Wifi libraries to allow a device (such as an iPhone) to connect to Greg. This will allow users to read descriptions, edited extra settings and view visualisation recordings. Read more about the Companion App on the [Aesthetic page](open-design-2018/development-asthetic/)


Used https://github.com/esp8266/arduino-esp8266fs-plugin to allow uploading of website to the esp8266 really easily.
