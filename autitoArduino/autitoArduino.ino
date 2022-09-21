#include "motor.h"
#include "encoder.h"
#include "steering.h"
#include "pew.h"

char cmd; // Stores the commands 

void setup() {
  MOTOR_init();
  ENCODER_init();
  STEERING_init();
  PEW_init();

  Serial.begin(9600); // Serial communication with the ESP8266 

  pinMode(LED_BUILTIN, OUTPUT); // Built-in led will be used for feedback while executing commands
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {
  if (Serial.available() > 0) { // Handle received commands from the ESP8266
    cmd = Serial.read();
    digitalWrite(LED_BUILTIN, HIGH); // Built-in led shines while executing commands
    switch (cmd) {
      case 'F':
        MOTOR_forward_P();
        break;
      case 'B':
        MOTOR_backward_P();
        break;
      case 'f':
        MOTOR_forward();
        break;
      case 'b':
        MOTOR_backward();
        break;
      case 'L':
        STEERING_turnLeft();
        delay(100);
        break;
      case 'R':
        STEERING_turnRight();
        delay(100);
        break;
      case 'P':
        PEW_pew();
        break;
      case 'S':
        MOTOR_stop();
        break;
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
}
