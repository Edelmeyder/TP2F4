#include "motor.h"
#include "encoder.h"
#include <Arduino.h>

volatile int state = 0; // 0: adelante; 1: atrás

void MOTOR_init() {
  pinMode(MOTOR_DIR_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  digitalWrite(MOTOR_DIR_PIN, HIGH);
  digitalWrite(MOTOR_PWM_PIN, HIGH);
}

int MOTOR_GET_STATE(){
  return state;
}

void MOTOR_forward() {
  if (state == 1) { // Si el motor está yendo hacia atrás se detiene y espera
    MOTOR_stop();
    delay(MOTOR_DELAY);
  }
  state = 0;
  digitalWrite(MOTOR_DIR_PIN, HIGH); // Dirección adelante
  analogWrite(MOTOR_PWM_PIN, 255-MOTOR_SPEED); // Velocidad en PWM
}

void MOTOR_backward() {
  if (state == 0) { // Si el motor está yendo hacia adelante se detiene y espera
    MOTOR_stop();
    delay(MOTOR_DELAY);
  }
  state = 1;
  digitalWrite(MOTOR_DIR_PIN, LOW); // Dirección atrás
  analogWrite(MOTOR_PWM_PIN, MOTOR_SPEED); // Velocidad en PWM
}

void MOTOR_forward_P() {
  MOTOR_forward(); // Setea dirección hacia adelante
  ENCODER_start(); // Le pide al encoder que empiece a contar una vuelta
  ENCODER_wait(); // Se bloquea hasta que el encoder cuente una vuelta
  MOTOR_stop(); // Detiene el motor

}
void MOTOR_backward_P() {
  MOTOR_backward(); // Setea dirección hacia atrás
  ENCODER_start(); // Le pide al encoder que empiece a contar una vuelta
  ENCODER_wait(); // Se bloquea hasta que el encoder cuente una vuelta
  MOTOR_stop(); // Detiene el motor
}

void MOTOR_stop() {
  digitalWrite(MOTOR_DIR_PIN, HIGH);  //Dirección adelante
  digitalWrite(MOTOR_PWM_PIN, HIGH);  //Velocidad 0
}
