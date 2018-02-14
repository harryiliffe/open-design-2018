#include "FastLED.h"

#define NUM_LEDS 1
#define DATA_PIN 12



CRGB leds[NUM_LEDS];

Ticker ledblink;
bool ledon = false;

void leds_loop() {
  if (ledon) {
    leds[0] = CRGB::Black;
    ledon = !ledon;
  } else {
    leds[0] = CRGB::Green;
    ledon = !ledon;
  }
  FastLED.show();
}

void leds_setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  ledblink.attach(1, leds_loop);
}

