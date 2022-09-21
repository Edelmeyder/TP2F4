#include "encoder.h"
#include <Arduino.h>

void INT_handler(void);

int pulses;

static volatile unsigned long debounce = 0; // Used to debounce encoder pulses

void ENCODER_init() {
  pinMode(ENCODER_PIN, INPUT);
  attachInterrupt(0, INT_handler, RISING); // Sets the interruption handler
  noInterrupts(); 
}

void ENCODER_start() {
  pulses = 0;
  interrupts(); // Starts interruptions to count pulses
}

int ENCODER_wait() {
  if (pulses >= ENCODER_HOLES) { // A whole turn has been made
    noInterrupts(); // Stops interruptions
    return 0;
  }
  return 1;
}

void INT_handler() {
  if (digitalRead(ENCODER_PIN) && (micros() - debounce > 500) && digitalRead(ENCODER_PIN)) {
    // Checks again if the signal is high and if the debounce time has passed; then checks the signal one more time
    debounce = micros(); // Stores current time for deboncing
  
    pulses++; // Takes a pulse
  }
}
