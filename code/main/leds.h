

#define NUM_LEDS 5
#define DATA_PIN 14
#define MAXFADECOUNT 40
#define FADEDURATION 5000


CRGB leds[NUM_LEDS];

Ticker ledblink;

Ticker stroke;
bool stroking = false;
int strokeNumber = 0;
int strokeLEDNumber = 0;
int strokeLEDCount = 0;
CHSV strokeColor;


bool ledon = false;
bool flipped = false;
bool switchcheck = false;
int startFrom = 0;

Ticker ledFader;
int fadeCount = 0;

void leds_show(bool overide) {
  if ((modes[modeEnabled].ledsEnabled && modes[0].ledsEnabled) || overide) {
    FastLED.show();
  }
}

void leds_setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
}

void leds_fade() {
  if (fadeCount > 0) {
    fadeCount--;
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i].subtractFromRGB(255 / MAXFADECOUNT);
    }
  } else {
    ledFader.detach();
  }
  leds_show(false);
}

void leds_stroke() {
  if (!stroking) {
    stroke.detach();
    stroke.attach_ms(250, leds_stroke);
    strokeLEDNumber = 0;
    fadeCount = MAXFADECOUNT;
    ledFader.attach_ms(FADEDURATION / MAXFADECOUNT, leds_fade);
  }
  stroking = true;
  if (strokeNumber < 1) {
    if (strokeLEDNumber < NUM_LEDS) {
      leds[strokeLEDNumber] = strokeColor;
      strokeLEDNumber++;
    } else {
      strokeNumber++;
      strokeLEDNumber = 0;
    }
  } else {
    stroke.detach();
    strokeNumber = 0;
    stroking = false;
  }
  leds_show(false);
}

void leds_modeChange() {
  if (!stroking) {
    stroking = true;
    stroke.detach();
    strokeLEDNumber = 0;
    stroke.attach_ms(250, leds_modeChange);
  }
  
  if (strokeNumber < 1) {
    if (strokeLEDNumber < NUM_LEDS) {
      leds[strokeLEDNumber] = modes[modeSelection].color;
      strokeLEDNumber++;
    } else {
      strokeNumber++;
      strokeLEDNumber = 0;
    }
  } else {
    stroke.detach();
    strokeNumber = 0;
    stroking = false;
  }
  leds_show(false);
}


void flipleds() {
  Serial.println(map(radtodeg(ypr[1]), -90, 90, 0, 255));
  fill_solid(leds, NUM_LEDS, CHSV(map(radtodeg(ypr[1]), -90, 90, 0, 255), 255, 255));
  leds_show(false);
}





//void leds_stroke(int start) {
//  if (!stroking) {
//    strokeLEDNumber = start;
//    Serial.println("Started New Stroke");
//  }
//  stroking = true;
//  if (strokeNumber < 1) {
//    if (strokeLEDNumber > 0 && strokeLEDNumber < NUM_LEDS + 1) {
//      leds[strokeLEDNumber - 1] = CRGB::Black;
//      Serial.println("blacked led " + String(strokeLEDNumber - 1));
//    }
//    if (strokeLEDNumber < NUM_LEDS && strokeLEDCount != 0) {
//      strokeLEDCount--;
//      leds[strokeLEDNumber] = CRGB::Red;
//      Serial.println("lit led " + String(strokeLEDNumber));
//      strokeLEDNumber++;
//
//    } else {
//      strokeNumber++;
//      strokeLEDNumber = 0;
//      Serial.println("added to strokenumber");
//    }
//  } else {
//    stroke.detach();
//    strokeNumber = 0;
//    stroking = false;
//    Serial.println("Finishing Stroke");
//  }
//  leds_show(false);
//}



