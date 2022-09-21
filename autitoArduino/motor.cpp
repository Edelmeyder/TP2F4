#include "motor.h"
#include "encoder.h"
#include <Arduino.h>

int state = 0; // 0: stopped; 1: forward; 2: backward

void MOTOR_init() {
  pinMode(MOTOR_DIR_PIN, OUTPUT);
  pinMode(MOTOR_PWM_PIN, OUTPUT);
  digitalWrite(MOTOR_DIR_PIN, HIGH);
  digitalWrite(MOTOR_PWM_PIN, HIGH);
}

void MOTOR_forward() {
  if (state == 2) { // If the motor is currently going backwards stop and wait
    MOTOR_stop();
    delay(MOTOR_DELAY);
  }
  state = 1;
  digitalWrite(MOTOR_DIR_PIN, HIGH);    // direction = forward
  analogWrite(MOTOR_PWM_PIN, 255-SP);   // PWM speed
}

void MOTOR_backward() {
  if (state == 1) { // If the motor is currently going forwards stop and wait
    MOTOR_stop();
    delay(MOTOR_DELAY);
  }
  state = 2;
  digitalWrite(MOTOR_DIR_PIN, LOW);     // direction = backward
  analogWrite(MOTOR_PWM_PIN, 255-SP);   // PWM speed
}

void MOTOR_forward_P() {
  MOTOR_forward();
  ENCODER_start();
  while (ENCODER_wait());
  MOTOR_stop();
}
void MOTOR_backward_P() {
  MOTOR_backward();
  ENCODER_start();
  while (ENCODER_wait());
  MOTOR_stop();
}

void MOTOR_stop() {
  digitalWrite(MOTOR_PWM_PIN, HIGH);
  state = 0;
}
