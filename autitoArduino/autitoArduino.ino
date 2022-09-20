#include "motor.h"

char req;

void setup() {
  MOTOR_init();

}

void loop() {
  if (Serial.available() > 0) {
    req = Serial.read();
    digitalWrite(LED_BUILTIN, HIGH);
    switch (req) {
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
        break;
      case 'R':
        break;
      case 'P':
        break;
      case 'S':
        MOTOR_stop();
        break;
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
}
