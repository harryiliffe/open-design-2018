#include <ArduinoJson.h>

#include "Wire.h"

#include <Ticker.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "FastLED.h"


//DEFINATIONS

void strokeDetect(int i);
void modeInit();

StaticJsonBuffer<200> jsonBuffer;



int modeSelection = 0;

Ticker debug;

struct Mode {
  String name;
  CRGB color;
  bool enabled;
  bool strokeAdjustment;
};

int modeEnabled = 0;

#define NUM_MODES 5

Mode modes[NUM_MODES] = {
  {"Switch", CRGB::White, true, false},
  {"Idle", CRGB::Blue, false, true},
  {"Hide & Seek", CRGB::Aqua, false, false},
  {"Greg Says", CRGB::Green, false, false},
  {"Visualise", CRGB::Yellow, false, false},
};


#include "mpu.h"
#include "leds.h"
#include "touch.h"
#include "wifi.h"

void setup() {
  Serial.begin(72880);

  String realSize = String(ESP.getFlashChipRealSize());
  String ideSize = String(ESP.getFlashChipSize());
  bool flashCorrectlyConfigured = realSize.equals(ideSize);

  if(!flashCorrectlyConfigured){ Serial.println("flash incorrectly configured, SPIFFS cannot start, IDE size: " + ideSize + ", real size: " + realSize);}

  Serial.println("Starting Code");
  Wire.begin();
  leds_setup();
  mpu_setup();
  modeInit();
  wifi_setup();
  FastLED.setBrightness(20);
  //  debug.attach(1, readYPR);
}



void loop() {
  wifi_loop();

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
    case 2:
      break;
    case 3:
      break;
    case 4:
      break;
  }
  FastLED.show();
}


