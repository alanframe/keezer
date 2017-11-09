#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

extern float Beer1Temperature;
extern float Beer2Temperature;
extern float SetTemperature;
extern float FreezerTemperature;
extern float FreezerSetTemperature;
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
  Beer1Temperature = sensors.getTempCByIndex(0);
  Beer2Temperature = sensors.getTempCByIndex(1);
  FreezerTemperature = sensors.getTempCByIndex(2);
}



void controlTemp(){
  // for debug now
  
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
  FreezerSetTemperature = SetTemperature + (SetTemperature - (Beer1Temperature + Beer2Temperature)/2) * 1.5;
  Serial.print("Freezer Set Temperature =");
  Serial.println(FreezerSetTemperature);
  Serial.print("Freezer Temperature =");
  Serial.println(FreezerTemperature);

  if (FreezerSetTemperature < FreezerTemperature){
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
