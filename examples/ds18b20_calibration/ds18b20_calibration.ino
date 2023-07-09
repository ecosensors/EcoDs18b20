/*
 * HOW TO CALIBRATE A DS18B20
 * 
 * To correct the rawValue (the value measured with the sensor), you should previously measure the temperature of the iced (env.0°)
 * and the boild water (env. 97°). We will use that script to measure the iced and boiled water in order to save the value as 
 * 'refMin and 'refMax'
 * 
 * You need to prepare an iced water glass (Placed the glass in a freezer) in order to measure min reference temperature (refMin)
 * Boil some water to measure the max reference temperature (You should measure 96°-97°) - (refMax)
 * You can use an accurate termometer to measure the reference values
 * Note: The measured value depends of the atmospheric pressure
 * 
 * Place the DS18B20 sensor into the iced water and run the script to have measured temperature (tMin). 
 * Repeat the operation with the sensor into the boiled water (tMax)
 * 
 * float corrected1 = ecods18b20.corrected(&rawValue, tMin, refMin, tMax - tMin, refMax - refMin);
 * 
 * 
 * In that example, I am using a PCF8574 to power the sensor. If you don't, comment the PCF8574 part and use 
 * 'pinMode(pinPower, OUTPUT);' and 'digitalWrite(pinPower,HIGH);' instead of 'expander.digitalWrite(powerPin, (powerWhenHigh)? HIGH : LOW);'
 * Adapt the script as you need.
 * 
 */

#include <OneWire.h>
#include <Ecods18b20.h>
#include "PCF8574.h"

bool powerWhenHigh = true;
int powerPin = 4;           // select the pin used with the PCF8574 to power the sensor
byte pinRead=19; //A1

// Change the values after you measured the iced and boiled water with the sensor and an accurate termometer
float tMin = 16;                // Sensor value
float tMax = 101;               // sensor value
float refMin= -0.4;             // accurate termometer
float refMax = 97.6;            // accurate termometer
float rawRange = tMax-tMin;
float refRange = refMax-refMin;

OneWire ds(pinRead); // read the sensors at the pin19 (A1)
Ecods18b20 ecods18b20;
PCF8574 expander;



void setup() {
  Serial.begin(9600);

  delay(8000);

  Serial.println(F("     ECOBOARD     "));
  Serial.println(F(" DS18B20 CALIBRATION "));
  Serial.println(F("------------------"));
  Serial.println(F(""));

  Serial.println(F("\r\nSETUP"));
  Serial.println(F("==================="));

  pinMode(pinRead, INPUT_PULLUP);
  
  /*
  * PCF8574
  */
  Serial.println(F("\r\n# Start PCF8574"));
  expander.begin(0x27);
  expander.pinMode(0, OUTPUT);
  expander.pinMode(1, OUTPUT);
  expander.pinMode(2, OUTPUT);
  expander.pinMode(3, OUTPUT);
  expander.pinMode(4, OUTPUT);
  expander.pinMode(5, OUTPUT);
  expander.pinMode(6, OUTPUT);

  Serial.println(F("Testing PCF"));
  for (int p = 1; p < 7; p++) {
    expander.digitalWrite(p, LOW);
    delay(50);
    //delayMicroseconds(50000);
    Serial.print(F("\tP")); Serial.print(p); Serial.print(F(":"));
    Serial.println(expander.digitalRead(p) ? "HIGH" : "LOW");
    delay(50);
    //delayMicroseconds(50000);
  }
}

void loop() {

  Serial.println(F("\r\nDS18B20 measures for calibration"));
  Serial.println(F("******************************"));

  float temperature_soil;

  expander.digitalWrite(powerPin, (powerWhenHigh)? HIGH : LOW);
  // digitalWrite(pinPower,HIGH);
  delay(750);
  
  if(ecods18b20.get_temperature(&ds, &temperature_soil, true)==1)
  {
    Serial.print(F("\t"));Serial.print((int16_t)temperature_soil); Serial.println(F("C"));
    float corrected = ecods18b20.corrected(&temperature_soil, tMin, refMin, rawRange, refRange);
    Serial.print(F("\tCorrected: "));Serial.print((int16_t)corrected); Serial.println(F("C"));
  }
  expander.digitalWrite(powerPin, (!powerWhenHigh)? HIGH : LOW);
  // digitalWrite(pinPower,LOW);
  
  delay(250);
}