#ifndef _MOTOR_H
#define _MOTOR_H

// MOTOR Speed & direction F/B
#define MOTOR_PWM_PIN D5 // Motor PWM pin
#define MOTOR_DIR_PIN D1 // Motor Direction pin
#define MOTOR_SPEED 200

#define MOTOR_DELAY 500  // Needed to avoid overloading motors by quickly changing rotation direction

void MOTOR_init(void);        // Initialises motor related pins
void MOTOR_forward(void);     // Sets the motor forwards
void MOTOR_backward(void);    // Sets the motor backwards
void MOTOR_forward_P(void);   // Turns the wheel one turn forward
void MOTOR_backward_P(void);  // Turns the wheel one turn backward
void MOTOR_stop(void);        // Stops the motor
int MOTOR_GET_STATE(void);     //return the state of the motor

#endif
