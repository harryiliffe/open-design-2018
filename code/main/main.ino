
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
void sound_arf();
void sound_ruff();
void sound_chirp();
void sound_meow();
void sound_meow2();
void sound_mew();
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

int modeEnabled = 1;

#define NUM_MODES 6

#define MODE_SWITCH 0
#define MODE_IDLE 1
#define MODE_HIDESEEK 2
#define MODE_GREGSAYS 3
#define MODE_GREGSINGS 4
#define MODE_VISUALISE 5

Mode modes[NUM_MODES] = {
  {0, "Main Menu", 0xffffff, true, false, true, 1, 1},
  {1, "Emo Greg", CRGB::Green, false, true, true, 1, 1},
  {2, "Hide & Seek", CRGB::Yellow, false, false, true, 1, 1},
  {3, "Greg Says", CRGB::Aqua, false, false, false, 1, 1},
  {4, "Greg Sings", CRGB::Purple, false, false, false, 1, 1},
  {5, "Visualise", CRGB::Red, false, false, true, 1, 1},
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
  pinMode(SPEAKER, OUTPUT);
  startSPIFFS();
  config_load();

  wifi_setup();

  Wire.begin();
  leds_setup();
  mpu_setup();
  modeInit();

  //  FastLED.setBrightness(20);
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
    case MODE_GREGSINGS:
      gregSing();
      break;
  }

}


void strokeDetect(int i) {
  switch (modeEnabled) {
    case MODE_SWITCH:
      swipeMode();
      break;
    case MODE_IDLE:
      if (!stroking) {
        strokeColor = CHSV(strokeColor.hue + 6, 255, 255);
      }
      leds_stroke();
      if (random(0, 1) == 1 && !stroking) {
        switch (random(0, 4)) {
          case 1:
            sound_meow2();
            break;
          case 2:
            sound_mew();
            break;
          case 3:
            sound_chirp();
            break;
        }
      }
      break;
  }
}

void swipeMode() {
  modeSelection++;
  if (modeSelection >= NUM_MODES) {
    modeSelection = 1;
  }
  leds_modeChange();
  Serial.println("Mode Selection: " + modes[modeSelection].title);
}

void modeInit() {
  switch (modeEnabled) {
    case MODE_SWITCH:
      modeSelection = modeEnabled;
      leds_modeChange();
      break;
    case MODE_IDLE: //IDLE
      strokeColor = CHSV(random8(), 255, 255);
      fill_solid(leds, NUM_LEDS, strokeColor);
      break;
    case MODE_HIDESEEK: //HIDE&SEEK
      fill_solid(leds, NUM_LEDS, CRGB::Red);
      break;
    case MODE_GREGSAYS: //GREGSAYS
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      gregSays_setup();
      break;
    case MODE_VISUALISE: //VISUALISE
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      break;
    case MODE_GREGSINGS: //VISUALISE
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      for (int i = 4; i > -1; i--) {
        sound_playTone(i, 470, false, true);
        delay(500);
      }
      break;
  }
  leds_show(true);
}

