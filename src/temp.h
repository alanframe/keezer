#ifndef HEADER_TEMP
  #define HEADER_TEMP
  #include <DallasTemperature.h>
  //Prototype for helper_function found in HelperFunctions.cpp
  void InitTempSensors();
  void UpdateSensorTemps();
  void controlTemp();
#endif
