
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




int modeSelection = 0;

struct Mode {
  int id;
  String title;
  CRGB color;
  bool enabled;
  bool strokeAdjustment;
  bool strokeEnabled;
  bool soundEnabled;
  bool ledsEnabled;
};

int modeEnabled = 0;

#define NUM_MODES 6

#define MODE_SWITCH 0
#define MODE_IDLE 1
#define MODE_HIDESEEK 2
#define MODE_GREGSAYS 3
#define MODE_VISUALISE 4
#define MODE_SING 5

Mode modes[NUM_MODES] = {
  {0, "Main Menu", CRGB::White, true, false, true, 1, 1},
  {1, "Emo Greg", 0xb3d99e, false, true, true, 1, 1},
  {2, "Hide & Seek", 0x79cbca, false, false, true, 1, 1},
  {3, "Greg Says", 0xfcd486, false, false, false, 1, 1},
  {4, "Greg Sings", 0x85d4eb, false, false, false, 1, 1},
  {5, "Visualise", 0xf19b96, false, false, true, 1, 1},
};

#include "config.h"
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
  if (!flashCorrectlyConfigured) {
    Serial.println("flash incorrectly configured, SPIFFS cannot start, IDE size: " + ideSize + ", real size: " + realSize);
  }
  
  startSPIFFS();
  config_load();
  
  wifi_setup();
  Serial.println("Starting Code");
  Wire.begin();
  leds_setup();
  mpu_setup();
  modeInit();

  FastLED.setBrightness(20);
}



void loop() {
  wifi_loop();
  touch_read();

  switch (modeEnabled) {
    case MODE_GREGSAYS:
      if (respondSequence) {
        greySays_respond();
      }
      break;
    case MODE_VISUALISE:
      mpu_loop();
      flipleds();
      break;

  }

}


void strokeDetect(int i) {
  switch (modeEnabled) {
    case MODE_SWITCH:
      swipeMode();
      break;
    case MODE_IDLE:
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
  Serial.println("Mode Selection: " + modes[modeSelection].title);
}

void modeInit() {
  switch (modeEnabled) {
    case MODE_SWITCH:
      modeSelection = modeEnabled;
      leds_modeChange(modes[modeEnabled].color);
      break;
    case MODE_IDLE: //IDLE
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
    case MODE_HIDESEEK: //HIDE&SEEK
      //      fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
    case MODE_GREGSAYS: //GREGSAYS
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      gregSays_setup();
      break;
    case MODE_VISUALISE: //VISUALISE
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
    case MODE_SING: //VISUALISE
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
  }
  FastLED.show();
}


