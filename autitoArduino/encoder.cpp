#include "encoder.h"
#include <Arduino.h>

int pulses;

unsigned long timetick;

int ENCODER_read(void);

void ENCODER_init() {
  pinMode(ENCODER_PIN, INPUT_PULLUP);
}

void ENCODER_start() {
  pulses = 0;
}

void ENCODER_wait() {
  timetick = millis(); // Used to prevent infinite loop in case no pulses are read
  while (pulses < ENCODER_HOLES && (millis() - timetick) < 500) {
    if (ENCODER_read()) { // A whole turn has been made
      pulses++;
    }
    delayMicroseconds(10);
  }
}

int ENCODER_read() {
  // Encoder read should be called periodically on a higher frequency than encoder pulses; at least double
  static int oldValue = 0;
  static int lastValidValue = 0;
  byte value;
  value = digitalRead(ENCODER_PIN);
  if (value == oldValue & value != lastValidValue) { // Second debounce and multiple detection prevention
    lastValidValue = value;
    return value;
  }
  oldValue = value; // First debounce
  return 0;
}
