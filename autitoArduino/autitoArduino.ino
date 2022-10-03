#include "motor.h"
#include "encoder.h"
#include "steering.h"
#include "pew.h"
#include "sensor.h"

char cmd; // Stores the commands 
int colision_state; //1 si hay objeto delante

void setup() {
  MOTOR_init();
  ENCODER_init();
  STEERING_init();
  PEW_init();
  SENSOR_init();
  colision_state=0;

  Serial.begin(9600); // Serial communication with the ESP8266 

  pinMode(LED_BUILTIN, OUTPUT); // Built-in led will be used for feedback while executing commands
  digitalWrite(LED_BUILTIN, LOW);
}

void loop() {

  colision_state=SENSOR_Verif_Colision();

  if (colision_state){  //pooling sensor, 1 si se detecto objeto

    if (!MOTOR_GET_STATE()){  //si es 0 debemos pararlo
      MOTOR_stop();
    }
  }
  
  if (Serial.available() > 0) { // Handle received commands from the ESP8266
    cmd = Serial.read();
    digitalWrite(LED_BUILTIN, HIGH); // Built-in led shines while executing commands
    switch (cmd) {
      case 'F':
        if(!colision_state){
          MOTOR_forward_P();
        }
        break;
      case 'B':
        MOTOR_backward_P();
        break;
      case 'f':
        if(!colision_state){
          MOTOR_forward();
        }
        break;
      case 'b':
        MOTOR_backward();
        break;
      case 'L':
        STEERING_turnLeft();
        delay(100);
        break;
      case 'R':
        STEERING_turnRight();
        delay(100);
        break;
      case 'P':
        PEW_pew();
        break;
      case 'S':
        MOTOR_stop();
        break;
    }
    digitalWrite(LED_BUILTIN, LOW);
  }
}
