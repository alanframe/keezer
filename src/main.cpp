#include <Arduino.h>
#include "temp.h"
#include "Configuration.h"
#include "maindisplay.h"
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <WiFiManager.h>

//
MDNSResponder mdns;

// Setup some variables
float Beer1Temperature;
float Beer2Temperature;
float SetTemperature;
float FreezerTemperature;
float FreezerSetTemperature;
bool Cooling;
char Beer1Name[20];
char Beer2Name[20];
ESP8266WebServer server(80);
String webPage = "";


void setup(void)
{
  SetTemperature = 12;
  pinMode(D0, OUTPUT);
  // start serial port
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Kegerator V0.3");
  WiFiManager wifiManager;
  //reset saved settings
  //wifiManager.resetSettings();
  wifiManager.autoConnect("AutoConnectAP");
  Serial.println("connected...yeey :)");
  //WiFi.begin(ssid, password);
  Serial.println("");


  if (mdns.begin("esp8266", WiFi.localIP())) {
    Serial.println("MDNS responder started");
  }

  server.on("/", [](){
  server.send(200, "text/html", webPage);
  });

  server.on("/tup", [](){
  SetTemperature += 0.5;
  server.send(200, "text/html", webPage);
  });

  server.on("/tdown", [](){
  SetTemperature -= 0.5;
  server.send(200, "text/html", webPage);
  });

  server.begin();
  Serial.println("HTTP server started");

  // Setup Main OLED_CS
  MDisplayInit();

  // Configuration loading
  configuration_initalise();
  bool ConfigurationState = IsConfigured();
  if (ConfigurationState) {
    Serial.println("Configuration found");
  }
  else {
    Serial.println("No Configuration found");
  }



  // Initalise the temperature sensors.
  InitTempSensors();

  // Default state is not cooling at startup.
  digitalWrite(D0,LOW);
  Cooling = false;
}

// The main program Loop

void loop(void)
{


  UpdateSensorTemps();
  MDisplayNorm(FreezerTemperature,Beer1Temperature,Beer2Temperature,FreezerSetTemperature,Cooling);
  controlTemp();
  webPage = "<h1>Kegerator is Online !</h1><p>Set Temperature =";
  webPage += SetTemperature;
  webPage += "<br>Freezer Target Temperature =";
  webPage += FreezerSetTemperature;
  webPage += "<br>Freezer Temperature =";
  webPage += FreezerTemperature;
  webPage += "<br>Beer 1 Temperature =";
  webPage += Beer1Temperature;
  webPage += "<br>Beer 2 Temperature =";
  webPage += Beer2Temperature;
  server.handleClient();


}
