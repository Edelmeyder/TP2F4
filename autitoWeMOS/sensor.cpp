#include "sensor.h"
#include <Arduino.h>


long duracion, distancia; 
const float FACTOR = 0.01715;  //vel sonido (0.0343cm/us) / 2

long SENSOR_Calc_dist (void);
void SENSOR_Generate_Pulse (void);

void SENSOR_init() {
  pinMode(Pecho, INPUT);     // define el pin Pecho como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin Ptrig como salida  (trigger)

  digitalWrite(Ptrig, LOW);
  delayMicroseconds(5);
}

/// Función que genera un pulso por el pin de trigger
void SENSOR_Generate_Pulse (){

  digitalWrite(Ptrig, LOW); // para generar pulso limpio ponemos a LOW por 5us
  delayMicroseconds(5);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de trigger por 10us, luego del cual el sensor enviara 8 pulsos de 40Khz 
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
  
}

/// Función que calcula la distancia en centímetros
long SENSOR_Calc_dist (){

  //pulso de echo mas largo es => (400cm(dist max) * 1us / 0.0343cm)*2 (ida y vuelta) = 23,32 ms  ==> tomamos 30ms por si acaso para el timeout del echo... 
  duracion = pulseIn(Pecho, HIGH, 30000);   // mide tiempo de pulso en estado HIGH, el cual sera igual al tiempo transcurrido entre enviar y recibir un ping, timeout de 30000us si no llega señal de echo
  distancia = duracion * FACTOR;            // calcula la distancia en centímetros
  return distancia;
  
}

int SENSOR_Verif_Collision(){  

  SENSOR_Generate_Pulse();

  long distancia_cm = SENSOR_Calc_dist();
  /* Por alguna razón el sensor retorna cada tanto valores incorrectos de distancias
  pequeñas (0 - 7 cm aprox) no encontramos el porqué pero se soluciona ignorándolas
  con el siguiente if. Hay 8 cm desde el sensor hasta el frente del autito así que
  medidas en ese rango no serían relevantes de cualquier manera.
  */
  if(distancia_cm < 8){  // se paso de rango
    // retornar que no hay objeto delante
    return 0;
  }
  if (distancia_cm<SENSOR_UMBRAL){  // objeto entre (0,30) cm
    return 1;
  }else{
    return 0;
  }
  
}
