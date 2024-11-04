#include <Arduino.h>

/* Number of PIN where the HIGH should be detected that comes from SIG_PIN */
const int SWITCH_DETECT_PIN = GPIO_NUM_4;

void setup() {
  Serial.begin(9600);

  // Set detect pin as input
  pinMode(SWITCH_DETECT_PIN, INPUT);
}

void loop() {
  Serial.println(digitalRead(SWITCH_DETECT_PIN));
  delay(1000);
}
