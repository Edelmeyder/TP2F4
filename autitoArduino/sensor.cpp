#include "sensor.h"
#include <Arduino.h>


long duracion, distancia;  


void SENSOR_init() {
  pinMode(Pecho, INPUT);     // define el pin Pecho como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin Ptrig como salida  (triger)

  digitalWrite(Ptrig, LOW);
  delayMicroseconds(2);
}


void SENSOR_Generate_Pulse (){ //funcion que genera un pulso por el pin de trigger

  delayMicroseconds(2);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10us
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
  
}

long SENSOR_Calc_dist (){  //funcion que calcula la distancia en centimetros

  duracion = pulseIn(Pecho, HIGH);
  distancia = (duracion/2) / 29;            // calcula la distancia en centimetros
  return distancia;
  
}

int SENSOR_Verif_Colision(){  //funcion que verifica si hay algun objeto delante

  SENSOR_Generate_Pulse();

  if (SENSOR_Calc_dist()<SENSOR_UMBRAL){
    return 1;
  }else{
    return 0;
  }
  
}