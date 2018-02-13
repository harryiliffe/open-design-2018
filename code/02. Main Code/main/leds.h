  

#define NUM_LEDS 5
#define DATA_PIN 14



CRGB leds[NUM_LEDS];

Ticker ledblink;

Ticker stroke;
bool stroking = false;
int strokeNumber = 0;
int strokeLEDNumber = 0;
int strokeLEDCount = 0;
CRGB strokeColor;


bool ledon = false;
bool flipped = false;
bool switchcheck = false;
int startFrom = 0;

void leds_blinkloop() {
  if (ledon && !flipped) {
    fill_solid(leds, NUM_LEDS, CRGB::Purple);
    ledon = !ledon;
  } else if (ledon && flipped) {
    fill_solid(leds, NUM_LEDS, CRGB::Red);
    ledon = !ledon;
  } else {
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    ledon = !ledon;
  }
  FastLED.show();
}

void leds_setup() {
  FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
  //  ledblink.attach(1, leds_blinkloop);
}

void leds_stroke(int start) {
  if (!stroking) {
    strokeLEDNumber = start;
    Serial.println("Started New Stroke");
  }
  stroking = true;
  if (strokeNumber < 1) {
    if (strokeLEDNumber > 0 && strokeLEDNumber < NUM_LEDS + 1) {
      leds[strokeLEDNumber - 1] = CRGB::Black;
      Serial.println("blacked led " + String(strokeLEDNumber - 1));
    }
    if (strokeLEDNumber < NUM_LEDS && strokeLEDCount != 0) {
      strokeLEDCount--;
      leds[strokeLEDNumber] = CRGB::Red;
      Serial.println("lit led " + String(strokeLEDNumber));
      strokeLEDNumber++;
      
    } else {
      strokeNumber++;
      strokeLEDNumber = 0;
      Serial.println("added to strokenumber");
    }
  } else {
    stroke.detach();
    strokeNumber = 0;
    stroking = false;
    Serial.println("Finishing Stroke");
  }
  FastLED.show();
}


void leds_modeChange(CRGB color) {
  if (!stroking) {
    stroke.attach_ms(100, leds_modeChange, color);
    strokeLEDNumber = 0;
    strokeColor = color;
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
  FastLED.show();
}


void flipleds() {
  Serial.println(map(radtodeg(ypr[1]), -90, 90, 0, 255));
  fill_solid(leds, NUM_LEDS, CHSV(map(radtodeg(ypr[1]), -90, 90, 0, 255), 255, 255));
  FastLED.show();
}


