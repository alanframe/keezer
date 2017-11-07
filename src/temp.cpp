#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

extern float Beer1Temprature;
extern float Beer2Temprature;
extern float SetTemprature;
extern float FreezerTemprature;
extern float FreezerSetTemprature;
extern bool Cooling;

unsigned long CurrentTime;
unsigned long StopTime;
unsigned long CyclingPeriod;

// Data wire is plugged into port 2 on the Arduino
#define ONE_WIRE_BUS D2

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)

OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);



void InitTempSensors() {
    sensors.begin();
    Serial.print("Found ");
    Serial.print(sensors.getDeviceCount(), DEC);
    Serial.println(" devices.");
    StopTime = 0;
}

void UpdateSensorTemps(){
  sensors.requestTemperatures();
  Beer1Temprature = sensors.getTempCByIndex(0);
  Beer2Temprature = sensors.getTempCByIndex(1);
  FreezerTemprature = sensors.getTempCByIndex(2);
}



void controlTemp(){
  // for debug now
  SetTemprature = 27;
  CyclingPeriod = 40000;
  UpdateSensorTemps();

  // Check if we are in the anti cycling period.
  CurrentTime = millis();
  if (CurrentTime - StopTime > CyclingPeriod){
    Serial.println(CurrentTime);
    Serial.println(StopTime);
    Serial.println("Out of Cycling Period");
  }
  else {
    Serial.println(CurrentTime);
    Serial.println(StopTime);
    Serial.println("Inside Cycling Period");
    return;
  }
  // Got to here so okay to cool if needed
  FreezerSetTemprature = SetTemprature + (SetTemprature - (Beer1Temprature + Beer2Temprature)/2) * 1.5;
  Serial.println("FreezerSetTemprature =");
  Serial.println(FreezerSetTemprature);

  if (FreezerSetTemprature < FreezerTemprature){
    // Turn cooling on
    Serial.println("Cooling On");
  }
  else {
    Serial.println("Cooling Off");
    StopTime = millis();
  }
}
