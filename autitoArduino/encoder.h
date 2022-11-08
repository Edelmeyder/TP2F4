#ifndef _ENCODER_H
#define _ENCODER_H

#define ENCODER_PIN D2     // Encoder pin
#define ENCODER_HOLES 20  // Number of holes on a single turn
#define ENCODER_WHEEL_DIAMETER 0.065 // Diameter of the wheel

void ENCODER_init(void);  // Initializes encoder related pins
void ENCODER_start(void); // Starts counting pulses
float ENCODER_distance(void); // Return distance since last call
void ENCODER_wait(void);   // Waits until a full turn has been made since the call

#endif
