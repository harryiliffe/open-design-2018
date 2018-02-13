#define SPEAKER 16

bool playingNote = false;
Ticker noteTimer;
Ticker lightTimer;

int tones[] = {261, 294, 330, 349, 392};
CRGB toneColors[] = {CRGB::Red, CRGB::Green, CRGB::Yellow, CRGB::Blue, CRGB::Purple};
//            mid C  D    E    F    G


void sound_playTone(int toneRef, int duration, bool overide, bool lights) {
  if (!playingNote || overide) {
    Serial.printf("Playing Note %i\n", toneRef);
    playingNote = true;
    noTone(SPEAKER);
    tone(SPEAKER, tones[toneRef]);
    if (lights) {
      leds[toneRef] = toneColors[toneRef];
      FastLED.show();
      lightTimer.once_ms(duration - 30, sound_stopLights, toneRef);
    }
    noteTimer.once_ms(duration, sound_stopTone, SPEAKER);
  }
}

void sound_stopLights(int light) {
  leds[light] = CRGB::Black;
  FastLED.show();
}

void sound_stopTone(int pin){
  noTone(pin);
  Serial.println("Stopping Note");
  playingNote = false;
}

