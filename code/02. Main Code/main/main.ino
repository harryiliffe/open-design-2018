//#include "ota.h"
#include "Wire.h"

#include <Ticker.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "FastLED.h"


//DEFINATIONS

void strokeDetect(int i);
void modeInit();



#define NUM_MODES 7

int modeSelection = 0;

Ticker debug;

struct Mode {
  String name;
  CRGB color;
  bool enabled;
  bool strokeAdjustment;
};

int modeEnabled = 0;

Mode modes[NUM_MODES] = {
  {"Switch", CRGB::White, true, false},
  {"Idle", CRGB::Blue, false, true},
  {"Gyro Color Change", CRGB::Aqua, false, false},
  {"Other Mode 2", CRGB::Green, false, false},
  {"Other Mode 3", CRGB::Yellow, false, false},
  {"Other Mode 5", CRGB::Red, false, false},
  {"Other Mode 6", CRGB::Purple, false, false}
};


#include "mpu.h"
#include "leds.h"
#include "touch.h"

void setup() {
  Serial.begin(115200);
  Serial.println("Starting Code");
  Wire.begin();
//  ota_setup();
  leds_setup();
  //  while (!mpu_setup()) {}
  mpu_setup();
  modeInit();
  FastLED.setBrightness(20);
  //  debug.attach(1, readYPR);
}



void loop() {
//  ArduinoOTA.handle();

  mpu_loop();
  touch_read();

  switch (modeEnabled){
    case 2:
      flipleds();
      break;
  }
}


void strokeDetect(int i) {
  switch (modeEnabled) {
    case 0:
      swipeMode();
      break;
    case 1:
      leds_stroke(i);
      stroke.attach_ms(duration, leds_stroke, i);
      Serial.println("Stroke LEDS:" + String(duration) + " ms, from " + String(i));
      break;
  }
}

void swipeMode() {
  modeSelection++;
  if (modeSelection >= NUM_MODES) {
    modeSelection = 1;
  }
  leds_modeChange(modes[modeSelection].color);
  stroke.attach_ms(100, leds_modeChange, modes[modeSelection].color);
  Serial.println("Mode Selection: " + modes[modeSelection].name);
}

void modeInit() {
  switch (modeEnabled) {
    case 0:
      modeSelection = modeEnabled;
      leds_modeChange(modes[0].color);
      stroke.attach_ms(100, leds_modeChange, modes[0].color);
      break;
    case 1:
      fill_solid(leds, NUM_LEDS, CRGB::LightGrey);
      break;
  }
  FastLED.show();
}


