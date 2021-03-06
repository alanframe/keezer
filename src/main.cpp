#include <Arduino.h>
#include "temp.h"
#include "Configuration.h"
#include "maindisplay.h"
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>


// Setup some variables
float Beer1Temprature;
float Beer2Temprature;
float SetTemprature;
float FreezerTemprature;
float FreezerSetTemprature;
bool Cooling;
char Beer1Name[20];
char Beer2Name[20];




void setup(void)
{
  pinMode(D0, OUTPUT);
  // start serial port
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Kegerator V0.3");

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
  MDisplayNorm(FreezerTemprature,Beer1Temprature,Beer2Temprature,FreezerSetTemprature,Cooling);
  controlTemp();



}
