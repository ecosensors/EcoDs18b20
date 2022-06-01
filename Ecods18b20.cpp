/*
* EcoSensors
* Library is still under developpent
* 
* 
* 
* 
* 
*
* 
*/

#include "Arduino.h"
#include "Ecods18b20.h"
#include <OneWire.h>

/*
* You can connect up to 4 DS18B20, either on the same BUS, or a different pin for each of them.
* YOU MUST DEFINE THE Pin numer https://learn.adafruit.com/adafruit-feather-m0-adalogger/pinouts
* Expl:
* A0 => 14
* A1 => 15
* A2 => 16
* A3 => 17
* A4 => 18
* A5 => 19
* 
* pin_read1: Define here the pin which will read the value of the first sensor or NULL if you dont
* pin_read2: Define here the pin which will read the value of the second sensor or NULL if you dont
* pin_read3: Define here the pin which will read the value of the third sensor or NULL if you dont
* pin_read4: Define here the pin which will read the value of the fourth sensor or NULL if you dont
*/
Ecods18b20::Ecods18b20()
{
}

void Ecods18b20::begin(OneWire* ds)
{
	_ds = ds;

}
/*
* 1 = READ_OK
* 0 = NO_SENSOR_FOUND
* -1 = INVALID_ADDRESS
* -2 = INVALID_SENSOR
*/
int Ecods18b20::get_temperature(float *temperature_soil, byte reset_search)
{
	Serial.println(F("\r\nGetting temperature"));
    Serial.println(F("******************************"));
    
    delay(500);
    byte data[9], addr[8];
      // data[] : Données lues depuis le scratchpad
      // addr[] : Adresse du module 1-Wire détecté  
      // Reset le bus 1-Wire ci nécessaire (requis pour la lecture du premier capteur)
      if (reset_search) {
        _ds->reset_search();
      }
      // Recherche le prochain capteur 1-Wire disponible
      if (!_ds->search(addr)) {
        // Pas de capteur
        return 0;
      }   
      
      // Vérifie que l'adresse a été correctement reçue 
      if (OneWire::crc8(addr, 7) != addr[7])
      {
        // Adresse invalide
        return -1;
      }

      // Vérifie qu'il s'agit bien d'un DS18B20 
      if (addr[0] != 0x28)
      {
        return -2;
      }
      // Reset le bus 1-Wire et sélectionne le capteur
      _ds->reset();
      _ds->select(addr);
    
      // Lance une prise de mesure de température et attend la fin de la mesure
      _ds->write(0x44, 1);
      delay(800);
    
      // Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad
      _ds->reset();
      _ds->select(addr);
      _ds->write(0xBE);
   
      // Lecture du scratchpad
      for (byte i = 0; i < 9; i++) {
      data[i] = _ds->read();
    }
     
    // Calcul de la température en degré Celsius 
    *temperature_soil = (int16_t) ((data[1] << 8) | data[0]) * 0.0625;

    // Pas d'erreur

    return 1;
}

Ecods18b20::Ecods18b20(byte pin_read1, byte pin_read2, byte pin_read3, byte pin_read4)
{
	_pin_read1 = pin_read1;
	_pin_read2 = pin_read2;
	_pin_read3 = pin_read3;
	_pin_read4 = pin_read4;
	
}

void Ecods18b20::begin()
{
	Serial.println(F("\r\n**************************"));
	Serial.println(F("*    DS18B20 Library     *"));
	Serial.println(F("*   from EcoSensor.ch    *"));
	Serial.println(F("**************************"));

	if(_pin_read1 != NULL)
	{
		Serial.print(F("# Configures the pin ")); Serial.print(_pin_read1); Serial.println(F(" as input"));
		pinMode(_pin_read1, INPUT_PULLUP);
		delay(500);
		scan(_pin_read1);

	}
	else
		Serial.println(F("[Info] pin_read1 is NULL"));


	if(_pin_read2 != NULL)
	{
		Serial.print(F("# Configures the pin ")); Serial.print(_pin_read2); Serial.println(F(" as input"));
		pinMode(_pin_read2, INPUT_PULLUP);
		delay(500);
		scan(_pin_read2);
	}
	else
		Serial.println(F("[Info] pin_read2 is NULL"));


	if(_pin_read3 != NULL)
	{
		Serial.print(F("# Configures the pin ")); Serial.print(_pin_read3); Serial.println(F(" as input"));
		pinMode(_pin_read3, INPUT_PULLUP);
		delay(500);
		scan(_pin_read3);
	}
	else
		Serial.println(F("[Info] pin_read3 is NULL"));


	if(_pin_read4 != NULL)
	{
		Serial.print(F("# Configures the pin ")); Serial.print(_pin_read4); Serial.println(F(" as input"));
		pinMode(_pin_read4, INPUT_PULLUP);
		delay(500);
		scan(_pin_read4);
	}
	else
		Serial.println(F("[Info] pin_read4 is NULL"));

}

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
/*
* return:
* 1 => OK
* 0 => Mo sensor found
* -1 => Invalid address
* -2 => Wrong sensor. It's not a DS18B20
*
*/
int Ecods18b20::read(float *temperature, byte readPin, bool reset_search)
{
	//Serial.print(F("DEBUG read:")); Serial.println(readPin);

	OneWire dr(readPin);

	byte data[9], addr[8];
      // data[] : Données lues depuis le scratchpad
      // addr[] : Adresse du module 1-Wire détecté  
      // Reset the bus 1-Wire if necessary (require for the first read of the first sensor)
    if (reset_search)
    {
        dr.reset_search();
    }
    // Serach the next avaible 1-Wiere sensor
    if (!dr.search(addr)) {
    	Serial.println(F("No DS18B20 sensor"));
        return 0;
    }   
      
    // Check the sensor address 
    if (OneWire::crc8(addr, 7) != addr[7])
    {
    	Serial.println(F("Invalid address for the DS18B20 sensor"));
        return -1;
    }

    // Check if the sensor is a DS18B20 
    if (addr[0] != 0x28)
    {
        Serial.println(F("The sensor type does not belong to a DS18B29"));
        return -2;
    }
    
    // Reset the 1-Wire bus and select the sensor
    dr.reset();
    dr.select(addr);
    
    // Request a measure and wait for the end
    dr.write(0x44, 1);
    delay(800);
    
    // Reset the 1-Wire bus, select the sensor and request a read to the scratchpad
    dr.reset();
    dr.select(addr);
    dr.write(0xBE);
   
    // Read the scratchpad
    for (byte i = 0; i < 9; i++)
    {
      data[i] = dr.read();
    }
     
    // Calcul de la température en degré Celsius 
    *temperature = (int16_t) ((data[1] << 8) | data[0]) * 0.0625;

    return 1;
}

bool Ecods18b20::read1(float *temperature)
{	
	float t;
	//Serial.print(F("DEBUG read1: ")); Serial.println(_pin_read1);
	if(_pin_read1 == NULL)
	{
		//Serial.println(F("_pin_read1 is not defined"));
		return false;
	}
	read(&t, _pin_read1, true);
	*temperature = t;
	if(_pin_read1 != NULL)
		return true;
}

bool Ecods18b20::read2(float *temperature)
{	
	//Serial.print(F("DEBUG read2: ")); Serial.println(_pin_read2);
	float t;
	if(_pin_read2 == NULL)
	{
		//Serial.println(F("_pin_read2 is not defined"));
		return false;
	}
	read(&t, _pin_read2, true);
	*temperature = t;
	if(_pin_read2 != NULL)
		return true;
}

bool Ecods18b20::read3(float *temperature)
{	
	//Serial.print(F("DEBUG read3: ")); Serial.println(_pin_read3);
	float t;
	if(_pin_read3 == NULL)
	{
		//Serial.println(F("_pin_read3 is not defined"));
		return false;
	}
	read(&t, _pin_read3, true);
	*temperature = t;
	if(_pin_read3 != NULL)
		return true;
}

bool Ecods18b20::read4(float *temperature)
{	
	//Serial.print(F("DEBUG read4: ")); Serial.println(_pin_read4);
	float t;
	if(_pin_read4 == NULL)
	{
		//Serial.println(F("_pin_read4 is not defined"));
		return false;
	}
	read(&t, _pin_read4, true);
	*temperature = t;
	if(_pin_read4 != NULL)
		return true;
}