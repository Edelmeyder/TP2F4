#include "encoder.h"
#include "pew.h"
#include "motor.h"
#include "sensor.h"
#include <Arduino.h>

/*
  RPM / 60 = Revoluciones por segundo
  RPS * agujeros en el encoder = frecuencia de los pulsos
  1 / freq = periodo de los pulsos en segundos
  period * 1000 = periodo en milisegundos
  period in millis * 0.7 = El mínimo delay entre pulsos aceptado
*/
#define MIN_DELAY 700.0/((ENCODER_WHEEL_MAX_RPM / 60) * ENCODER_HOLES) 

volatile static int pulses;
volatile static long turns;
volatile static int turnStart;
volatile static int turn = 1;
volatile static long lastMillis = 0;
volatile static long actualMillis;

static int state;
static long waitTick;

IRAM_ATTR void encoderIntHandler() { // Manejador de interrupción para los pulsos del encoder
  actualMillis = millis();
  if (actualMillis - lastMillis < MIN_DELAY) { // Descarta pulsos demasiado rápidos que son ruido del encoder algunos provocados por vibraciones.
    return;
  }
  lastMillis = actualMillis;
  pulses++; 
  if (pulses == ENCODER_HOLES) { // Si se completó una vuelta
    turns++;
    pulses = 0;
  }
  if (!turn && pulses == turnStart) { // Si se hizo ENCODER_start() y se completó la vuelta
    turn = 1;
  } 
}

void ENCODER_init() {
  pulses = 0;
  turns = 0;
  pinMode(ENCODER_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(ENCODER_PIN), encoderIntHandler, RISING);
}

void ENCODER_start() {
  turnStart = pulses; // Guarda la posición actual de la rueda según el pulso
  turn = 0; // Variable que la interrupción cambia a 1 al completarse una vuelta
}

void ENCODER_wait() {
  waitTick = millis();
  state = MOTOR_GET_STATE();
  // Espera a que se complete una vuelta o halla pasado un segundo ( para no quedar bloqueado permanentemente en caso de fallos )
  while (!turn  && ((millis() - waitTick) < 1000) ){
    // Si durante la vuelta se detecta un obstáculo delante, se debe detener
    if (state == 0 && SENSOR_Verif_Collision()) {
      MOTOR_stop();
      break;      
    }
  }
}

float ENCODER_distance() {
  // Calcula y retorna la distancia
  if(pulses > 0)
    return ((float)turns + 1.0/pulses) * PI * ENCODER_WHEEL_DIAMETER;
  else
    return (float)turns * PI * ENCODER_WHEEL_DIAMETER;
}
