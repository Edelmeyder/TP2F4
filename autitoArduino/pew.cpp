#include "pew.h"
#include <Arduino.h>

void PEW_init() {
  pinMode(PEW_PIN, OUTPUT);
  digitalWrite(PEW_PIN, LOW);
}

void PEW_pew() {
  tone(PEW_PIN, 1000, 100); // 1000 Hz, 100 ms
}
