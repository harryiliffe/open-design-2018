#define SPEAKER 16

bool playingNote = false;
Ticker noteTimer;
Ticker lightTimer;

int tones[] = {261, 294, 330, 349, 392};
CRGB toneColors[] = {CRGB::Red, CRGB::Green, CRGB::Yellow, CRGB::Blue, CRGB::Purple};
//            mid C  D    E    F    G


void sound_playTone(int toneRef, int duration, bool overide, bool lights) {
  if (!modes[modeEnabled].soundEnabled || !modes[0].soundEnabled ) return;
  if (!playingNote || overide) {
    Serial.printf("Playing Note %i\n", toneRef);
    playingNote = true;
    noTone(SPEAKER);
    tone(SPEAKER, tones[toneRef]);
    if (lights) {
      leds[toneRef] = toneColors[toneRef];
      leds_show(false);
      lightTimer.once_ms(duration - 30, sound_stopLights, toneRef);
    }
    noteTimer.once_ms(duration, sound_stopTone, SPEAKER);
  }
}

void sound_stopLights(int light) {
  leds[light] = CRGB::Black;
  leds_show(false);
}

void sound_stopTone(int pin) {
  noTone(pin);
  Serial.println("Stopping Note");
  playingNote = false;
}


void playTone(uint16_t tone1, uint16_t duration) {
  if (tone1 < 50 || tone1 > 15000 || !modes[modeEnabled].soundEnabled || !modes[0].soundEnabled ) return; // these do not play on a piezo
  for (long i = 0; i < duration * 1000L; i += tone1 * 2) {
    digitalWrite(SPEAKER, HIGH);
    delayMicroseconds(tone1);
    digitalWrite(SPEAKER, LOW);
    delayMicroseconds(tone1);
  }
}

void sound_ruff() {   // dog ruff
  Serial.println("ruff");
  uint16_t i;
  for (i = 890; i < 910; i += 2) // "rrr"  (vary down)
    playTone(i, 3);
  playTone(1664, 150);        // "uuu" (hard to do)
  playTone(12200, 70);        // "ff"  (long, hard to do)
}

void sound_arf() {    // dog arf
  Serial.println("arf");
  uint16_t i;
  playTone(890, 25);         // "a"    (short)
  for (i = 890; i < 910; i += 2) // "rrr"  (vary down)
    playTone(i, 5);
  playTone(4545, 80);        // intermediate
  playTone(12200, 70);       // "ff"   (shorter, hard to do)
}


void sound_chirp() {  // Bird chirp
  Serial.println("chirp");
  for(uint8_t i=200; i>180; i--)
     playTone(i,9);
}

void sound_meow() {  // cat meow (emphasis ow "me")
  Serial.println("meow");
  uint16_t i;
  playTone(5100,50);        // "m" (short)
  playTone(394,180);        // "eee" (long)
  for(i=990; i<1022; i+=2)  // vary "ooo" down
     playTone(i,8);
  playTone(5100,40);        // "w" (short)
}

void sound_meow2() {  // cat meow (emphasis on "ow")
  Serial.println("meow2");
  uint16_t i;
  playTone(5100,55);       // "m" (short)
  playTone(394,170);       // "eee" (long)
  delay(30);               // wait a tiny bit
  for(i=330; i<360; i+=2)  // vary "ooo" down
     playTone(i,10);
  playTone(5100,40);       // "w" (short)
}

void sound_mew() {  // cat mew
  Serial.println("mew");
  uint16_t i;
  playTone(5100,55);       // "m"   (short)
  playTone(394,130);       // "eee" (long)
  playTone(384,35);        // "eee" (up a tiny bit on end)
  playTone(5100,40);       // "w"   (short)
}


