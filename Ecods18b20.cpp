/*
* EcoSensors
* Library is distributed  WITHOUT WARRANTY
* 
*/

#include "Arduino.h"
#include "Ecods18b20.h"


/*
* You can connect up to 4 DS18B20, either on the same BUS, or a different pin for each of them.
* YOU MUST DEFINE THE Pin number https://learn.adafruit.com/adafruit-feather-m0-adalogger/pinouts
* Expl:
* A0 => 14
* A1 => 15
* A2 => 16
* A3 => 17
* A4 => 18
* A5 => 19
* 
*/

Ecods18b20::Ecods18b20()
{
}

/*
* 1 = READ_OK
* 0 = NO_SENSOR_FOUND
* -1 = INVALID_ADDRESS
* -2 = INVALID_SENSOR
*/
int Ecods18b20::get_temperature(OneWire* ds, float *temperature_soil, bool reset_search)
{
	_wire = ds; // Does it makes sens to do it

	//Serial.println(F("Getting temperature"));
    
    delay(500);
    byte data[9], addr[8];
    // data[] : Données lues depuis le scratchpad
    // addr[] : Adresse du module 1-Wire détecté  
    // Reset le bus 1-Wire ci nécessaire (requis pour la lecture du premier capteur)
    
    if (reset_search) {
     	_wire->reset_search();
     }
     
      // Recherche le prochain capteur 1-Wire disponible
     if (!_wire->search(addr)) {
        // Pas de capteur
        Serial.println(F("No sensor found"));
     	return 0;
     }
     else
     {
     	switch (addr[0]) {
     		case 0x10:
     			Serial.println("  Chip = DS18S20");  // or old DS1820
     			break;
     		case 0x28:
	     		Serial.println("  Chip = DS18B20");
	     		break;
	     	case 0x22:
	     		Serial.println("  Chip = DS1822");
	     		break;
	     	default:
	     		Serial.println("Device is not a DS18x20 family device.");
	     		return -2;
	     } 

     }	
    
      // Vérifie que l'adresse a été correctement reçue 
     if (OneWire::crc8(addr, 7) != addr[7])
     {
     	// Adresse invalide
     	Serial.println(F("Invalid address"));
     	return -1;
     }
  
     // Vérifie qu'il s'agit bien d'un DS18B20 
     if (addr[0] != 0x28)
     {
     	Serial.println(F("Invalid sensor"));
     	return -2;
     }

     // the first ROM byte indicates which chip
	
     // Reset le bus 1-Wire et sélectionne le capteur
     _wire->reset();
     _wire->select(addr);
    
     // Lance une prise de mesure de température et attend la fin de la mesure
     _wire->write(0x44, 1);
     delay(800);
    
     // Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad
     _wire->reset();
     _wire->select(addr);
     _wire->write(0xBE);
   
      // Lecture du scratchpad
    for (byte i = 0; i < 9; i++) {
     	data[i] = _wire->read();
    }
    
    // Calcul de la température en degré Celsius 
    *temperature_soil = (int16_t) ((data[1] << 8) | data[0]) * 0.0625;

    // Pas d'erreur

    return 1;
}


float Ecods18b20::corrected(float *temperature, float rawLow, float referenceLow, float rawRange, float referenceRange)
{
  //Return the calculate value following the calibration step
  float correctedValue;

  //RawRange = RawHigh - RawLow
  //ReferenceRange = ReferenceHigh - ReferenceLow

  correctedValue = (((*temperature - rawLow) * referenceRange) / rawRange) + referenceLow;
  return correctedValue;
}


/*
void Ecods18b20::scan(byte readPin)
{
	Serial.print(F("# Scan DS18B20 on BUS ")); Serial.println(readPin);
	OneWire ds(readPin);
	int s = 0;
	do{
		byte address[8];
		if (!ds.search(address))
        {
          ds.reset_search();
          _numberOfConnectedSensors = s;
          Serial.print(F("Found "));
          Serial.print(_numberOfConnectedSensors);
          Serial.println(F(" sensor(s)"));
          s=4;  // Leave the loop
        }
        else
        {
          // DS18B20 has been found
          Serial.print(F("Found: "));
          for(byte i = 0; i < 8; ++i)
          {
            if (address[i] < 0x10) Serial.write('0');
            Serial.print(address[i], HEX);
            _sensorsAddr[readPin][s][i]=address[i];             // Save into an array to use it later
            Serial.write(' ');
          }

          // Check if the address belong to a DS18B20 
          if (OneWire::crc8(address, 7) != address[7])
          {
            Serial.print(F("(CRC invalid)"));
          }
          else
          {
          	
	        switch (address[0]) {
	           case 0x10:
	                Serial.println(F("  Chip = DS18S20"));  // or old DS1820
	             	break;
	            case 0x28:
	                Serial.println(F("  Chip = DS18B20"));
	             	break;
	            case 0x22:
	                Serial.println(F("  Chip = DS1822"));
	             	break;
	             default:
	             	Serial.println(F(" Unknow sensor!"));
	             	break;
	        }   
      		
          }
          s++;
          // END
          //Serial.println();
        }
      }while(s < 4);
}

*/