#include <ArduinoJson.h>

#include "Wire.h"

#include <Ticker.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"
#include "FastLED.h"


//DEFINATIONS===================================================================

void strokeDetect(int i);
void modeInit();
void sound_stopLights(int light);
void sound_stopTone(int pin);
void greySays_playLevel();
void greySays_respond();
//===================================================================


StaticJsonBuffer<200> jsonBuffer;



int modeSelection = 0;

Ticker debug;

struct Mode {
  int id;
  String name;
  CRGB color;
  bool enabled;
  bool strokeAdjustment;
  bool strokeEnabled;
};

int modeEnabled = 0;

#define NUM_MODES 5

Mode modes[NUM_MODES] = {
  {0, "Switch", CRGB::White, true, false, true},
  {1, "Idle", CRGB::Blue, false, true, true},
  {2, "Hide & Seek", CRGB::Aqua, false, false, true},
  {3, "Greg Says", CRGB::Green, false, false, false},
  {4, "Visualise", CRGB::Yellow, false, false, true},
};


#include "mpu.h"
#include "leds.h"
#include "touch.h"
#include "wifi.h"
#include "sound.h"
#include "gregsays.h"

void setup() {
  Serial.begin(72880);

  String realSize = String(ESP.getFlashChipRealSize());
  String ideSize = String(ESP.getFlashChipSize());
  bool flashCorrectlyConfigured = realSize.equals(ideSize);

  if(!flashCorrectlyConfigured){ Serial.println("flash incorrectly configured, SPIFFS cannot start, IDE size: " + ideSize + ", real size: " + realSize);}
  wifi_setup();
  Serial.println("Starting Code");
  Wire.begin();
  leds_setup();
  mpu_setup();
  modeInit();

  FastLED.setBrightness(20);
  //  debug.attach(1, readYPR);
}



void loop() {
  wifi_loop();
  touch_read();

  switch (modeEnabled){
    case 3:
      if(respondSequence){greySays_respond();}
      break;
    case 4:
      mpu_loop();
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
  Serial.println("Mode Selection: " + modes[modeSelection].name);
}

void modeInit() {
  switch (modeEnabled) {
    case 0:
      modeSelection = modeEnabled;
      leds_modeChange(modes[modeEnabled].color);
      break;
    case 1: //IDLE
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
    case 2: //HIDE&SEEK
//      fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
    case 3: //GREGSAYS
      gregSays_setup();
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
    case 4: //VISUALISE
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
  }
  FastLED.show();
}


