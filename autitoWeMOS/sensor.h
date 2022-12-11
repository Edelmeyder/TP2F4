#ifndef _SENSOR_H
#define _SENSOR_H

#define Pecho D0
#define Ptrig D2

#define SENSOR_UMBRAL 30 // Medida a partir de la cuál detecta un obstáculo, en centímetros

/// Inicializa los pines del sensor
void SENSOR_init(void);
/// Función que verifica si hay algún objeto delante dentro del umbral, retorna 1 si lo hay, 0 en caso contrario
int SENSOR_Verif_Collision(void);


#endif  //sensor
