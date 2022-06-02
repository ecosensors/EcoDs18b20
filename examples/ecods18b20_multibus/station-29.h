struct t_ds18b20 { // for DS18B20 calibration
  const byte pinPower;
  const byte pinRead;
  float refMin; // Temperature of the ice
  float refMax; // Temprature of the boiled water
  float tMin;   // Measure in the ice
  float tMax;   // Measure in the boiled water
};

struct ini_station
{
  const char* nom;
  const int station_id;
  const bool bud1_active;             // b1;
  t_ds18b20 bud1_config;      
  const bool bud2_active;             // b2;
  t_ds18b20 bud2_config;   
  const bool bud3_active;             // b3;
  t_ds18b20 bud3_config;  
  const bool bud4_active;             // b4;
  t_ds18b20 bud4_config;      
  const bool temperature_soil_active; // ts;
  t_ds18b20 tsoil_config;
};

ini_station station = {
    "Station 29",       // Station name
    29,                 // station ID
    true,
    {1,14,0,97,0,0},    // b1; ds18b20 calibration: powerPin, Analog  readPin, refMin, refMax, min, max
    false,              // 0=Unactive; 14=A0; *15=A1*; 16=A2; 17=A3; 18=A4; 19=A5
    {2,15,0,97,0,0},    // b2; ds18b20 calibration: powerPin, Analog  readPin, refMin, refMax, min, max
    false,              // 
    {3,16,0,97,0,0},    // b3; ds18b20 calibration: powerPin, Analog  readPin, refMin, refMax, min, max
    false,              // 
    {4,17,0,97,0,0},    // b4; ds18b20 calibration: powerPin, Analog  readPin, refMin, refMax, min, max
    true,               // 
    {4,19,0,97,0, 97},  // ts: ds18b20 calibration: powerPin, Analog  readPin, refMin, refMax, min, max
    
};

/*
 * refMin, refMax, min, max is used to compensate the value
 * That part will be done later
 */
