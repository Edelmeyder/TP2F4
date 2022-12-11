#ifndef _ENCODER_H
#define _ENCODER_H

#define ENCODER_PIN D7 // Pin del encoder
#define ENCODER_HOLES 20 // Número de agujeros en una vuelta del encoder
#define ENCODER_WHEEL_DIAMETER 0.065 // Diámetro de la rueda
#define ENCODER_WHEEL_MAX_RPM 170 // Máximas rpm de la rueda según el sitio web (no es el máximo real)

/// Inicializa el pin, las variables y la interrupción del encoder
void ENCODER_init(void);
/// Comienza a contar una vuelta
void ENCODER_start(void);
/// Bloquea el control hasta que se cumpla una vuelta desde la última llamada a ENCODER_start()
void ENCODER_wait(void);
/// Retorna la distancia (en metros) recorrida desde ENCODER_init()
float ENCODER_distance(void);


#endif
