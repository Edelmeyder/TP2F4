#include "steering.h"
#include <Arduino.h>

Servo steering;

int pos = STRGHT;         // Posición inicial es derecho

void STEERING_init() {
  steering.attach(STEERING_PIN);
  steering.write(STRGHT);
}

int STEERING_turnRight() {
  if (pos - 6 > MAX_L) {
    pos -= 6;
    steering.write(pos);
    return 1;
  } 
  return 0;
}
int STEERING_turnLeft() {
  if (pos + 6 < MAX_R) {
    pos += 6;
    steering.write(pos);
    return 1;
  } 
  return 0;
}
