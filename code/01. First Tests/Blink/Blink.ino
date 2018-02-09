/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
// Pin 13 has an LED connected on most Arduino boards.
// Pin 11 has the LED on Teensy 2.0
// Pin 6  has the LED on Teensy++ 2.0
// Pin 13 has the LED on Teensy 3.0
// give it a name:
int led = BUILTIN_LED;
  bool ledon = false;
  
// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  Serial.begin(74880);

}

// the loop routine runs over and over again forever:
void loop() {
  Serial.println("Look Ma, Im working");
  ledon = !ledon;
  digitalWrite(led, ledon);
  delay(1000);
}
