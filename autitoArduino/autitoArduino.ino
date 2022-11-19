#include "motor.h"
#include "encoder.h"
#include "steering.h"
#include "pew.h"
#include "sensor.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "index.h"
#define SIZE 256
#define DISTANCE_OVERFLOW 300

const float THRESHOLD = 10; //cada 10 metros escanea WiFi
//AP SSID and Password
const char* ssid = "AutoWiFi1";
const char* password = "12345678";

ESP8266WebServer server(80); //Web server

DynamicJsonDocument data(16384);

String s = MAIN_page; 
String req;
int charndx; 
String dataString;
int colision_state; //1 si hay objeto delante
int iC,iW;
float actualDistance, lastDistance = -10.1;
int checkDistanceCount = 0;

void menu(char cmd)
{
  switch (cmd) {
      case 'F':
        if(!SENSOR_Verif_Colision()){
          MOTOR_forward_P();
        }
        data["commands"][iC]["value"] = "F";
        break;
      case 'B':
        MOTOR_backward_P();
        data["commands"][iC]["value"] = "B";
        break;
      case 'f':
        if(!colision_state){
          MOTOR_forward();
        }
        data["commands"][iC]["value"] = "f";
        break;
      case 'b':
        MOTOR_backward();
        data["commands"][iC]["value"] = "b";
        break;
      case 'L':
        STEERING_turnLeft();
        data["commands"][iC]["value"] = "L";
        delay(100);
        break;
      case 'R':
        STEERING_turnRight();
        data["commands"][iC]["value"] = "R";
        delay(100);
        break;
      case 'P':
        //PEW_pew();
        data["commands"][iC]["value"] = "P";
        break;
      case 'S':
        MOTOR_stop();
        data["commands"][iC]["value"] = "S";
        break;
    }
}

void handleData()
{
  data["indexC"] = iC;
  data["indexW"] = iW;
  data["time"] = millis();
  data["distance"] = ENCODER_distance();
  serializeJson(data, dataString);
  server.send(200, "text/plain",dataString);
  data.clear();
  dataString = "";
  iC = 0;
  iW = 0;
}

void handleRoot() 
{
  if (server.args() == 0)    // reply with index if no argument...
  {
    server.send(200, "text/html", s);   //Send index(html)
  }
  else
  {
    req = server.argName(0);
    if (req.c_str()[0] != 'E')   // E ==> sequence, != E ==> the name is the command...
    {
      server.send(200, "text/plain", "ok");
      menu(req.c_str()[0]);
      data["commands"][iC]["date"] = server.argName(1);
      iC = (iC + 1 ) % SIZE;
    }
    else
    {
      server.send(200, "text/plain", "ok");
      req = server.arg(0);
      charndx = 0;
      
      while ( isAlpha(req.charAt(charndx)) ) 
      {
        menu(req.charAt(charndx));
        data["commands"][iC]["date"] = server.argName(1);
        iC = (iC + 1 ) % SIZE;
        charndx++;
      }
    }
  }
}

void setup() {
  delay(1000);
  iC = 0;
  iW = 0;
  MOTOR_init();
  ENCODER_init();
  STEERING_init();
  PEW_init();
  SENSOR_init();
  colision_state=0;
  MOTOR_stop();
  delay(3000);
  Serial.begin(115200);
  Serial.println();
  Serial.println("Configuring access point...");

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);
  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);

  server.on("/", handleRoot);
  server.on("/data", handleData);

  server.begin();

  Serial.println("Server started");

  PEW_all_ok();
}

void checkDistance(){
  actualDistance = ENCODER_distance();
  if((actualDistance - lastDistance) > THRESHOLD){
    lastDistance = actualDistance;
    WiFi.scanNetworksAsync(onScanComplete);
  }
}

void onScanComplete(int networks){
  int wifiTime = millis();
  for (int j = 0; j < networks; j++){
    data["wifi"][iW]["SSID"] = WiFi.SSID(j);
    data["wifi"][iW]["RSSI"] = WiFi.RSSI(j);
    data["wifi"][iW]["time"] = wifiTime;
    iW = (iW + 1) % SIZE;
  }
}

void loop() {
  colision_state=SENSOR_Verif_Colision();

  if (colision_state){  //pooling sensor, 1 si se detecto objeto

    if (!MOTOR_GET_STATE()){  //si es 0 es porque va hacia adelante entonces debemos pararlo
      MOTOR_stop();
    }
  }
  checkDistanceCount++;
  
  if(checkDistanceCount == DISTANCE_OVERFLOW){
    checkDistance();
    checkDistanceCount = 0;
  }

  server.handleClient();
  delay(2);
}
