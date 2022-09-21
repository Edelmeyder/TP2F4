#ifndef _STEERING_H
#define _STEERING_H

#include <Servo.h>

#define STEERING_PIN 5  // Pin to servo  
#define MAX_L 40        // Max. turn left  
#define MAX_R 115       // Max. turn right
#define STRGHT 85       // Streering stright direction

void STEERING_init(void);     // Initializes servo related pins and variables also makes the direcction straight
int STEERING_turnLeft(void);  // Steers left three steps if not at max_left position and returns 1; otherwise returns 0
int STEERING_turnRight(void); // Steers right three steps if not at max_right position and returns 1; otherwise returns 0


#endif
