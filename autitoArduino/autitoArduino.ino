#include "motor.h"
#include "encoder.h"
#include "steering.h"
#include "pew.h"
#include "sensor.h"
#include <ArduinoJson.h>
#define LED_PIN D5

#include <ESP8266WebServer.h>
#include "index.h"

//AP SSID and Password
const char* ssid = "AutoWiFi1";
const char* password = "12345678";

ESP8266WebServer server(80); //Web server

//char cmd; // Stores the commands 

/*data["distance"] = 0;
data["commands"]["forward"] = 0
data["commands"]["backward"] = 0;
{
  "distance" : 0,
  "commands" {
      "forward" : 0,
      "backward" : 0
  }
}*/
DynamicJsonDocument data(1024);
const int SIZE = 256;



int colision_state; //1 si hay objeto delante
int i;

void menu(char cmd)
{
  switch (cmd) {
      case 'F':
        if(!colision_state){
          MOTOR_forward_P();
        }
        data["commands"][i]["value"] = 'F';
        Serial.println("FORWARD_P");
        break;
      case 'B':
        MOTOR_backward_P();
        data["commands"][i]["value"] = 'B';
        Serial.println("BACK_P");
        break;
      case 'f':
        if(!colision_state){
          MOTOR_forward();
        }
        data["commands"][i]["value"] = "f";
        Serial.println("FORWARD");
        break;
      case 'b':
        MOTOR_backward();
        Serial.println("BACK");
        data["commands"][i]["value"] = "b";
        break;
      case 'L':
        STEERING_turnLeft();
        Serial.println("LEFT");
        data["commands"][i]["value"] = "L";
        delay(100);
        break;
      case 'R':
        STEERING_turnRight();
        Serial.println("RIGHT");
        data["commands"][i]["value"] = "R";
        delay(100);
        break;
      case 'P':
        PEW_pew();
        Serial.println("PEW");
        data["commands"][i]["value"] = "P";
        break;
      case 'S':
        MOTOR_stop();
        Serial.println("STOP");
        data["commands"][i]["value"] = "S";
        break;
    }
}

void handleData()
{
  data["index"] = i;
  String dataString;
  serializeJson(data, dataString);
  server.send(200, "text/plain",dataString);
  data.clear();
  i = 0 ;
}

void handleRoot() 
{
  String s = MAIN_page; 
  String req;
  int charndx; 


  if (server.args() == 0)    // reply with index if no argument...
  {
    server.send(200, "text/html", s);   //Send index(html)
  }
  else
  {
    req = server.argName(0);
    if (req.c_str()[0] != 'E')   // E ==> sequence, != E ==> the name is the command...
    {
      server.send(200, "text/html", s);   //Send index(html)
      menu(req.c_str()[0]);
      data["commands"][i]["date"] = server.argName(1);
       i = (i + 1 ) % SIZE;
    }
    else
    {
      server.send(200, "text/plain", "ok");
      req = server.arg(0);
      charndx = 0;
      
      while ( isAlpha(req.charAt(charndx)) ) 
      {
        menu(req.charAt(charndx));
        data["commands"][i]["date"] = server.argName(1);
        i = (i + 1 ) % SIZE;
        charndx++;
      }
    }
    Serial.flush();
  }
}

void setup() {
  delay(5000);
  //data["distance"] = 0;
  i = 0;
  MOTOR_init();
  ENCODER_init();
  STEERING_init();
  PEW_init();
  SENSOR_init();
  colision_state=0;
  MOTOR_stop();
delay(5000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  server.begin();
  Serial.println("Server started");

  server.on("/", handleRoot);
  server.on("/data", handleData);



  server.begin();
}

void loop() {
  colision_state=SENSOR_Verif_Colision();

  if (colision_state){  //pooling sensor, 1 si se detecto objeto

    if (!MOTOR_GET_STATE()){  //si es 0 es porque va hacia adelante entonces debemos pararlo
      MOTOR_stop();
    }
  }
  server.handleClient();
  delay(2);
}
