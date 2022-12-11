#ifndef _STEERING_H
#define _STEERING_H

#include <Servo.h>

#define STEERING_PIN D3  // Pin del servo  
#define MAX_L 40        // Max. giro izquierda
#define MAX_R 115       // Max. giro derecha
#define STRGHT 85       // Valor de posición derecho

/// Inicializa los pines y variables asociados al servo y setea la posición derecho
void STEERING_init(void);
/// Gira 3 pasos a la izquierda si no se ha alcanzado MAX_L y retorna 1; retorna 0 en caso contrario  
int STEERING_turnLeft(void);
/// Gira 3 pasos a la derecha si no se ha alcanzado MAX_R y retorna 1; retorna 0 en caso contrario
int STEERING_turnRight(void);

#endif
