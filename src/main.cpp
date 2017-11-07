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
char Beer1Name[20];
char Beer2Name[20];




void setup(void)
{
  pinMode(D0, OUTPUT);
  // start serial port
  Serial.begin(9600);
  Serial.println("");
  Serial.println("Kegerator V0.1");

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
}

// The main program Loop

void loop(void)
{


  UpdateSensorTemps();
  MDisplayNorm(Beer1Temprature,Beer2Temprature,FreezerTemprature,FreezerTemprature,true);
  controlTemp();



}
