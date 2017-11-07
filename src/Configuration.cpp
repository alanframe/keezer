#include <Arduino.h>
#include <EEPROM.h>
#include <DallasTemperature.h>

enum TempSensor {
  Beer1,
  Beer2,
  freezer
};

int ConfigAddress = 0; // 1 Byte
int DesiredTempAddress = 1; // 4 Bytes


bool IsConfigured( void ) {
  int state = EEPROM.read(ConfigAddress);
  if (state == 1) {
    return true;
  }
  else {
    return false;
  }
}

void SetConfigState( bool state ) {
  if (state == true) {
    EEPROM.write(ConfigAddress,1);
  }
  else {
    EEPROM.write(ConfigAddress,0);
  }
  EEPROM.commit();
}

void configuration_initalise( void ) {
  EEPROM.begin(512);
}






char* GetBeerName(int BeerIndex){
  // Read the beer name from EEprom

}
void SetBeerName( int BeerIndex, char* BeerName ){
  // Write the beer name to EEprom
}

float GetDesiredTemp(){
  // Read the desired Temprature from EEprom
  float Temprature;
  EEPROM.get(DesiredTempAddress, Temprature);
  return Temprature;
}

void SetDesiredTemp( float Temprature){
  // Write the desired Temprature to EEprom
  EEPROM.put(DesiredTempAddress, Temprature);
}
