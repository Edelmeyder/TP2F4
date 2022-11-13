#include "encoder.h"
#include "motor.h"
#include "sensor.h"
#include <Arduino.h>

/*
  RPM / 60 = revolutions per second
  RPS * encoder holes = fequency of pulses
  1 / freq = period of pulses in seconds
  period * 1000 = period in millis
  period in millis * 0.7 = the minimum delay between pulses accepted
*/
#define MIN_DELAY 700.0/((ENCODER_WHEEL_MAX_RPM / 60) * ENCODER_HOLES) 

volatile static long pulses;
volatile static long turns = 0;
volatile static int turnStart;
volatile static int turn = 1;
volatile static long waitTick;
volatile static long lastMillis = 0;
volatile static long actualMillis;

float distance = 0;

IRAM_ATTR void encoderIntHandler() {
  actualMillis = millis();
  if (actualMillis - lastMillis < MIN_DELAY) {
    return;
  }
  lastMillis = actualMillis;
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
  waitTick = millis();
  while (!turn  && ((millis() - waitTick) < 300) ){
    if (MOTOR_GET_STATE == 0 && SENSOR_Verif_Colision()) {
      break;      
    }
  }
}

float ENCODER_distance() {
  if(pulses > 0)
    distance = ((float)turns + 1.0/pulses) * PI * ENCODER_WHEEL_DIAMETER;
  else
    distance = (float)turns * PI * ENCODER_WHEEL_DIAMETER;
  return distance;
}



