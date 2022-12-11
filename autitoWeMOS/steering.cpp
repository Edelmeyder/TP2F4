#include "steering.h"
#include <Arduino.h>

Servo steering;

int pos = STRGHT;         // Initial position at "straight" value

void STEERING_init() {
  steering.attach(STEERING_PIN);
  steering.write(STRGHT);
}

int STEERING_turnRight() {
  if (pos - 3 > MAX_L) {
    pos -= 3;
    steering.write(pos);
    return 1;
  } 
  return 0;
}
int STEERING_turnLeft() {
  if (pos + 3 < MAX_R) {
    pos += 3;
    steering.write(pos);
    return 1;
  } 
  return 0;
}
