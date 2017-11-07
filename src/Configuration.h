#ifndef HEADER_CONFIGURATION
  #define HEADER_CONFIGURATION

  enum TempSensor {
    Beer1,
    Beer2,
    freezer
  };

  // Initalises EEPROM for use.
  void configuration_initalise( void );

  // Configuration State
  bool IsConfigured( void );
  void SetConfigState ( bool );



  // Beer Names
  char* GetBeerName(int );
  void SetBeerName( int, char[]  );

  //Desired Temperatures

  float GetDesiredTemp();
  void SetDesiredTemp( float );

  // Wifi

#endif
