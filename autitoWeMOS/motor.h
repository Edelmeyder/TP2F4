#ifndef _MOTOR_H
#define _MOTOR_H

#define MOTOR_PWM_PIN D5 // Motor pin de PWM
#define MOTOR_DIR_PIN D1 // Motor pin de dirección
#define MOTOR_SPEED 200  // Velocidad del pin 0 a 255 max. *Valores bajos no funcionan porque el motor no tiene el torque suficiente.

#define MOTOR_DELAY 500  // Delay necesario para evitar sobrecargar al motor al cambiar rápidamente de dirección

/// Inicializa los pines del motor
void MOTOR_init(void);
/// Motor hacia adelante, continuo
void MOTOR_forward(void);
/// Motor hacia atrás, continuo
void MOTOR_backward(void);
/// Gira la rueda una vuelta hacia adelante
void MOTOR_forward_P(void);
/// Gira la rueda una vuelta hacia atrás
void MOTOR_backward_P(void);
/// Detiene el motor
void MOTOR_stop(void);
/// Retorna el estado del motor: 0 adelante, 1 atrás
int MOTOR_GET_STATE(void);

#endif
