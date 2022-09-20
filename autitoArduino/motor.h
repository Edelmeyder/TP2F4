#ifndef _MOTOR_H
#define _MOTOR_H

// MOTOR Speed & direction F/B
#define MOTOR_PWM_PIN 6 // Motor PWM pin
#define MOTOR_DIR_PIN 7 // Motor Direction pin

#define MOTOR_DELAY 500  // Needed to avoid overloading motors by quickly changing rotation direction

void MOTOR_init(void);
void MOTOR_forward(void);
void MOTOR_backward(void);
void MOTOR_forward_P(void);
void MOTOR_backward_P(void);
void MOTOR_stop(void);

#endif
