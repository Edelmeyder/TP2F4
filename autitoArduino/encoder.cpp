#include "encoder.h"
#include <Arduino.h>

volatile static int pulses;
volatile static int turns = 0;
volatile static int turnStart;
volatile static int turn = 1;

int ENCODER_read(void);
void encoderIntHandler();

void ENCODER_init() {
  pinMode(ENCODER_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), encoderIntHandler, RISING);
}

void ENCODER_start() {
  turnStart = pulses;
  turn = 0;
}

void ENCODER_wait() {
  while (!turn);
}

void encoderIntHandler() {
  pulses++;
  if (pulses == ENCODER_HOLES) {
    turns++;
    pulses = 0;
  }
  if (!turn && pulses == turnStart) {
    turn = 1;
  } 
}
