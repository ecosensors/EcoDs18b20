

#ifndef Ecods18b20_h
#define Ecods18b20_h

#include <OneWire.h>

class Ecods18b20{
 	protected:

 	private:
 		OneWire* _ds;

 		byte _pin_read1;
 		byte _pin_read2;
 		byte _pin_read3;
 		byte _pin_read4;
 		int _numberOfConnectedSensors;
 		byte _sensorsAddr[4][4][8];
	
	public:
		Ecods18b20();
		Ecods18b20(byte read1, byte raed2, byte read3, byte read4);
		void start(OneWire* ds);
		int get_temperature(float *temperature_soil, bool reset_search);

		void begin();
		void scan(byte readPin);
		int read(float *temperature, byte readPin, bool reset_search);
		bool read1(float *temperature);
		bool read2(float *temperature);
		bool read3(float *temperature);
		bool read4(float *temperature);

		byte sensorsAddr[4][8];                // arrayto store the DS18B20 addresses. Max 4 sensors
  		int numberOfConnectedSensors = 0;
 
 };
 #endif