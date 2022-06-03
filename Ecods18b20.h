
/*
* EcoSensors
* Library is distributed WITHOUT WARRANTY
* 
*/

// Not used yet
enum DS18B20_RCODES {
  READ_OK,  // Lecture ok
  NO_SENSOR_FOUND,  // Pas de capteur
  INVALID_ADDRESS,  // Adresse reçue invalide
  INVALID_SENSOR  // Capteur invalide (pas un DS18B20)
};


#ifndef Ecods18b20_h
#define Ecods18b20_h

#include <OneWire.h>

class Ecods18b20{
 	protected:

 	private:
 		OneWire* _wire;
 		int _numberOfConnectedSensors;
 		byte _sensorsAddr[4][4][8];
 		
	
	public:
		Ecods18b20();
		int get_temperature(OneWire* ds, float *temperature_soil, bool reset_search);
		float corrected(float *temperature, float rawLow, float referenceLow, float rawRange, float referenceRange);
		void scan(byte readPin); // Not tested yet
 };
 #endif