#define PATTERNLENGTH 10

int pattern[PATTERNLENGTH];

bool playingSequence;
bool respondSequence;

int gameSpeed = 600;
int level;
int noteDuration;
int patternProgress;
int respondProgress;

Ticker patternTimer;

void gregSays_setup() {
  randomSeed(analogRead(A0));

  for (int i = 0; i < PATTERNLENGTH; i++) {
    pattern[i] = int(random(NUM_LEDS));
    Serial.printf("Got random number %i\n", pattern[i]);
  }
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  for (int i = 0; i < NUM_LEDS; i++) {
    sound_playTone(i, 470, false, true);
    delay(500);
  }
  level = 1;
  playingSequence = true;
  patternProgress = 0;
  gameSpeed = 800;
  noteDuration = gameSpeed * 0.875;
  delay(800);
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  leds_show(false);
  delay(800);
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  leds_show(false);
  delay(800);
  patternTimer.attach_ms(gameSpeed, greySays_playLevel);
  greySays_playLevel();
}

void greySays_playLevel() {
  //  Serial.printf("Playing note %i from sequence: %i\n", pattern[patternProgress], patternProgress);
  if (patternProgress < level) {
    sound_playTone(pattern[patternProgress], noteDuration, false, true);
    patternProgress++;
  } else {
    playingSequence = false;
    patternTimer.detach();
    greySays_respond();
  }
}


void greySays_respond() {
  if (!respondSequence) {
    //    Serial.println("Waiting for Responses");
    respondSequence = true;
    respondProgress = 0;
  }
  if (buttonState[pattern[respondProgress]].touch && !buttonState[pattern[respondProgress]].touchRegistered && touch_exclusive(pattern[respondProgress], 0, 5) && !playingNote ) {
    buttonState[pattern[respondProgress]].touchRegistered = true;
    sound_playTone(pattern[respondProgress], noteDuration, false, true);
    //    Serial.printf("Responding note %i from sequence: %i\n", pattern[respondProgress], respondProgress);
    respondProgress++;
  }
  if (respondProgress == level && !playingNote) {
    respondSequence = false;
    level++;
    Serial.printf("Congrats Level Up: Level %i\n", level);
    delay(300);
    fill_solid(leds, NUM_LEDS, CRGB::Green);
    leds_show(false);
    delay(400);
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    leds_show(false);
    delay(400);
    playingSequence = true;
    patternProgress = 0;
    greySays_playLevel();
    patternTimer.attach_ms(gameSpeed, greySays_playLevel);
  }
}

int singingNote = NULL;

void gregSing() {
  for (int i = 0; i < NUM_LEDS; i++) {
    if (buttonState[i].touch && !buttonState[i].touchRegistered) {
      singingNote = i;
      buttonState[i].touchRegistered = true;
      sound_playToneEndless(i, false, true);
    } else if (!buttonState[i].touch && singingNote == i) {
      singingNote = NULL;
      Serial.println("Stopping Note Via greg Sings");
      noTone(SPEAKER);
      fill_solid(leds, NUM_LEDS, CRGB::Black);
      leds_show(true);
    }
  }
}




