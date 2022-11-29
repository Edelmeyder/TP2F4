#ifndef _ENCODER_H
#define _ENCODER_H

#define ENCODER_PIN D7     // Encoder pin
#define ENCODER_HOLES 20  // Number of holes on a single turn
#define ENCODER_WHEEL_DIAMETER 0.065 // Diameter of the wheel
#define ENCODER_WHEEL_MAX_RPM 170 // Maximum rpm according to website (not the maximum on the car)

void ENCODER_init(void);  // Initializes encoder related pins
void ENCODER_start(void); // Starts counting pulses
float ENCODER_distance(void); // Return distance since last call
void ENCODER_wait(void);   // Waits until a full turn has been made since the call

#endif
