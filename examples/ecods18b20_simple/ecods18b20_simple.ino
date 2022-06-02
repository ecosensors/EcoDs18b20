/*
* The scrpt is distributed  WITHOUT WARRANTY
*/

#include <OneWire.h>
#include <Ecods18b20.h>

OneWire ds(19); // read the sensors at the pin19 (A1)
byte pinPower=10;
byte pinRead=19; //A1

Ecods18b20 ecods18b20;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  pinMode(pinPower, OUTPUT);
  digitalWrite(pinPower,LOW);
  pinMode(pinRead, INPUT_PULLUP);

  float temperature_soil;

  // Test it
  // Power the sensor
  digitalWrite(pinPower,HIGH);
  if(ecods18b20.get_temperature(&ds, &temperature_soil, true)==1)
  {
    Serial.print((int16_t)temperature_soil); Serial.println(F("C"));
  }
  digitalWrite(pinPower,LOW);

}

void loop() {
  // put your main code here, to run repeatedly:

}