#include "encoder.h"
#include <Arduino.h>

#define PI 3.14159265

volatile static int pulses;
volatile static int turns = 0;
volatile static int turnStart;
volatile static int turn = 1;

float distance = 0;

ICACHE_RAM_ATTR void encoderIntHandler() {
  pulses++;
  if (pulses == ENCODER_HOLES) {
    turns++;
    pulses = 0;
  }
  if (!turn && pulses == turnStart) {
    turn = 1;
  } 
}

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

float ENCODER_distance() {
  if(pulses > 0)
    distance = ((float)turns + 1.0/pulses) * PI * ENCODER_WHEEL_DIAMETER;
  else
    distance = (float)turns * PI * ENCODER_WHEEL_DIAMETER;
  //turns = 0;
  //pulses = 0;
  return distance;
}



