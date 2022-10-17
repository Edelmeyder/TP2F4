#ifndef _SENSOR_H
#define _SENSOR_H

#define Pecho D0
#define Ptrig D7

#define SENSOR_UMBRAL 30


void SENSOR_init(void);
void SENSOR_Generate_Pulse (void);
long SENSOR_Calc_dist (void);
int SENSOR_Verif_Colision(void);


#endif  //sensor
