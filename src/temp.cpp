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
    StopTime = 1000000;
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
    Serial.print("Current Time : ");
    Serial.println(CurrentTime);
    Serial.print("Stop Time : ");
    Serial.println(StopTime);
    Serial.println("Out of Cycling Period");
  }
  else {
    Serial.println(CurrentTime);
    Serial.print("Current Time : ");
    Serial.println(StopTime);
    Serial.print("Stop Time : ");
    Serial.println("Inside Cycling Period");
    return;
  }
  // Got to here so okay to cool if needed
  FreezerSetTemprature = SetTemprature + (SetTemprature - (Beer1Temprature + Beer2Temprature)/2) * 1.5;
  Serial.print("Freezer Set Temprature =");
  Serial.println(FreezerSetTemprature);
  Serial.print("Freezer Temprature =");
  Serial.println(FreezerTemprature);

  if (FreezerSetTemprature < FreezerTemprature){
    // Turn cooling on
    Serial.println("Cooling On");
    Cooling = true;
    digitalWrite(D0,HIGH);
  }
  else {
    if (Cooling){
      Serial.println("Cooling Off");
      Cooling = false;
      digitalWrite (D0,LOW);
      StopTime = millis();
    }
  }
}
