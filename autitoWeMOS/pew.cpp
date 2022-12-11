#include "pew.h"
#include <Arduino.h>

void PEW_init() {
  pinMode(PEW_PIN, OUTPUT);
  digitalWrite(PEW_PIN, LOW);
}

void PEW_pew() {
  tone(PEW_PIN, 1000, 150); // 1000 Hz, 100 ms
  delay(200);
}

void PEW_all_ok(){
  tone(PEW_PIN, 3000, 100); // 3000 Hz, 100 ms
  delay(130);

  tone(PEW_PIN, 3000, 100); // 3000 Hz, 100 ms
  delay(130);
}
