#include "sensor.h"
#include <Arduino.h>


long duracion, distancia; 

//pulso de echo mas largo es => (400cm(dist max) * 1us / 0.0343cm)*2 (ida y vuelta) = 23,32 ms  ==> tomamos 30ms por si acaso para el timeout del echo... 

const float FACTOR = 0.01715;  //vel sonido (0.0343cm/us) / 2


void SENSOR_init() {
  pinMode(Pecho, INPUT);     // define el pin Pecho como entrada (echo)
  pinMode(Ptrig, OUTPUT);    // define el pin Ptrig como salida  (triger)

  digitalWrite(Ptrig, LOW);
  delayMicroseconds(5);
}


void SENSOR_Generate_Pulse (){ //funcion que genera un pulso por el pin de trigger

  digitalWrite(Ptrig, LOW); // para generar pulso limpio ponemos a LOW por 5us
  delayMicroseconds(5);
  digitalWrite(Ptrig, HIGH);   // genera el pulso de triger por 10us, luego del cual el sensor enviara 8 pulsos de 40Khz 
  delayMicroseconds(10);
  digitalWrite(Ptrig, LOW);
  
}

long SENSOR_Calc_dist (){  //funcion que calcula la distancia en centimetros

  duracion = pulseIn(Pecho, HIGH, 30000);    //mide tiempo de pulso en estado HIGH, el cual sera igual al tiempo transcurrido entre enviar y recibir un ping, timeout de 30000us si no llega señal de echo
  distancia = duracion * FACTOR;            // calcula la distancia en centimetros
  return distancia;
  
}

int SENSOR_Verif_Colision(){  //funcion que verifica si hay algun objeto delante, return 1 si lo hay, 0 en caso contrario

  SENSOR_Generate_Pulse();

  long distancia_cm = SENSOR_Calc_dist();
  if(distancia_cm < 8){  //se paso de rango
    //no hacer nada por ahora, retornar que no hay objeto delante
    return 0;
  }
  if (distancia_cm<SENSOR_UMBRAL){  //objeto entre (0,30) cm
    return 1;
  }else{
    return 0;
  }
  
}
