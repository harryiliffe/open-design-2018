
#define ttp229 (0xAF>>1)
#define NUM_BUTTONS 16

#define LEGR1 15
#define LEGR2 13
#define LEGL1 14
#define LEGL2 12

uint16_t data_out = 0;
uint16_t data1, data2;

//bool buttonState[NUM_BUTTONS];


struct button {
  int touchStart;
  int touchEnd;
  bool touch;
  bool touchRegistered;
  String type;
};

int duration;


button buttonState[NUM_BUTTONS] = {
  {NULL, NULL, NULL, NULL, "stroke"}, //0
  {NULL, NULL, NULL, NULL, "stroke"}, //1
  {NULL, NULL, NULL, NULL, "stroke"}, //2
  {NULL, NULL, NULL, NULL, "stroke"}, //3
  {NULL, NULL, NULL, NULL, "stroke"}, //4
  {NULL, NULL, NULL, NULL, "null"}, //5
  {NULL, NULL, NULL, NULL, "null"}, //6
  {NULL, NULL, NULL, NULL, "null"}, //7
  {NULL, NULL, NULL, NULL, "null"}, //8
  {NULL, NULL, NULL, NULL, "null"}, //9
  {NULL, NULL, NULL, NULL, "null"}, //10
  {NULL, NULL, NULL, NULL, "null"}, //11
  {NULL, NULL, NULL, NULL, "leg"}, //12
  {NULL, NULL, NULL, NULL, "leg"}, //13
  {NULL, NULL, NULL, NULL, "leg"}, //14
  {NULL, NULL, NULL, NULL, "leg"}, //15
};

void touch_legDetect() {
  if (buttonState[LEGR1].touch && buttonState[LEGL1].touch && (!buttonState[LEGR1].touchRegistered || !buttonState[LEGL1].touchRegistered)) {
    buttonState[LEGR1].touchRegistered = true;
    buttonState[LEGL1].touchRegistered = true;
    if (modeEnabled == 0) {
      modeEnabled = modeSelection;
      Serial.println("Mode Changed: " + modes[modeEnabled].title);
      modeInit();
    } else {
      modeEnabled = 0;
      modeInit();
      Serial.println("Mode Changed: " + modes[modeEnabled].title);
    }
  }
}

void touch_read() {
  Wire.requestFrom(ttp229, 2, true);
  while (Wire.available())
  {
    data1 = Wire.read();
    data2 = Wire.read();
    data_out = (data1 << 8) | data2;
    for (int i = 0; i < NUM_BUTTONS; i++) {
      if (buttonState[i].type != "null") {
        if (bitRead(data_out, i) == 1 && buttonState[i].touch == false) {
          buttonState[i].touch = true;
          buttonState[i].touchStart = millis();
          buttonState[i].touchEnd = NULL;

        } else if (bitRead(data_out, i) == 0 && buttonState[i].touch == true) {
          buttonState[i].touch = false;
          buttonState[i].touchEnd = millis();
          buttonState[i].touchRegistered = false;
        }
      }
      if (buttonState[i].type == "stroke" && buttonState[i + 1].type == "stroke" && modes[modeEnabled].strokeEnabled) {
        if (!buttonState[i].touchRegistered) {
          if (buttonState[i].touchStart < buttonState[i + 1].touchStart) {
            duration = (buttonState[i + 1].touchStart - buttonState[i].touchStart);
            if (stroking && modes[modeEnabled].strokeAdjustment) {
              strokeLEDCount++;
              strokeDetect(i);
            }
            else if (!stroking) {
              strokeLEDCount = 2;
              strokeDetect(i);
            } else {
              //            Serial.println("Detected Stroke but did nothing");
            }
            buttonState[i].touchRegistered = true;
          }
        }
      }
      //            Serial.print(bitRead(data_out, i));
    }
    //        Serial.println();
  }
  touch_legDetect();
}

bool touch_exclusive(int button, int rangeMin, int rangeMax){
  for(int i=rangeMin; i<rangeMax;i++){
    if(buttonState[i].touch && i!=button){
      return false;
    }
  }
  return true;
}

