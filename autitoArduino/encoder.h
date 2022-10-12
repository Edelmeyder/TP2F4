#ifndef _ENCODER_H
#define _ENCODER_H

#define ENCODER_PIN 2     // Encoder pin
#define ENCODER_HOLES 30  // Number of holes on a single turn

void ENCODER_init(void);  // Initializes encoder related pins
void ENCODER_start(void); // Starts counting pulses
void ENCODER_wait(void);   // When a full turn has been made stops counting and returns 0; otherwise returns 1

#endif
