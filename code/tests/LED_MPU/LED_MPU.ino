#include <Ticker.h>
#include "I2Cdev.h"
#include "MPU6050_6Axis_MotionApps20.h"

#include "leds.h"
#include "mpu.h"


float threshhold = 2000.0;
int flag;
int steps = 0;
void setup() {
  leds_setup();
  mpu_setup();
}



void loop() {
  mpu_loop();

  if (accelVector > threshhold && flag == 0) {
    steps = steps + 1;
    flag = 1;
      Serial.println(accelVector);
  Serial.print("steps=");
  Serial.println(steps);
  }
  else if (accelVector > threshhold && flag == 1) {
    //do nothing
  }
  else if (accelVector < threshhold  && flag == 1) {
    flag = 0;
  }

}


