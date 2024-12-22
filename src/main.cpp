#include <Arduino.h>
#include <ESP32Servo.h>

/* Number of PIN where the HIGH should be detected that comes from SIG_PIN */
const int SWITCH_DETECT_PIN = GPIO_NUM_4;

const int PIN_SERVO_ARM = GPIO_NUM_26;
const int PIN_SERVO_DOOR = GPIO_NUM_27;

Servo servo;

int pos = 0;
int servoPin = 27;

// Starting position of servo
int startPos = 270;
// Position of the first pause
int pausePos = startPos - 90;
// End position (maximum movement of arm)
int endPos = pausePos - 90;

// The used servo somehow does not work like I wanted it to.
// This could happen because of misconfiguration of the frequency, pulse width etc.
// which I dont know the time of writing this...
// So to fix this, I have to calculate the degrees on a scale between 0 and 180 degress,
// because 180 degress is the maximum (and the servo always goes to 270)
float translateDegrees(int val) {
  if(val < 0) return 0;
  if(val > 270) return 180;
  return (val / 270.0) * 180.0;
}

void setup() {
  Serial.begin(9600);

  ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);

  servo.setPeriodHertz(333);
  servo.attach(servoPin, 500, 2500);
  servo.write(translateDegrees(startPos));

  // Set detect pin as input
  pinMode(SWITCH_DETECT_PIN, INPUT_PULLUP);
}

void run() {
  Serial.printf("Starting at position: %d \n", startPos);
  Serial.println(translateDegrees(startPos));

  // Go to pause position
  for(pos = startPos; pos > pausePos; --pos) {
		servo.write(translateDegrees(pos));    
		delay(8);
  }

  // Do pause position
  Serial.printf("Pause at position: %d \n", pos);
  Serial.println(translateDegrees(pos));
  delay(1000);

  // Go to end position
  for (pos = pausePos; pos > endPos; --pos) { 
		servo.write(translateDegrees(pos));    
		delay(4);
	}

  Serial.printf("Ended at position: %d \n", pos);
  Serial.println(translateDegrees(pos));
  delay(8);

  // Go to start position
	for (pos = endPos; pos < startPos; ++pos) {
		servo.write(translateDegrees(pos));
		delay(4);
	}

  Serial.printf("Returned to position: %d \n", pos);
  Serial.println(translateDegrees(pos));
}

void loop() {
  if(digitalRead(SWITCH_DETECT_PIN) == LOW) {
    run();
  };
}






