#include <OneWire.h>
#include <Ecods18b20.h>

OneWire ds(19);               // read the sensors at the pin19 (A1)
// Later, I will have to investigate how to adapt my code 1 or serveral pins where are connected other ds18b20 sensors
// The idea is from a configuration file, I activate 3 sensors and the call will be change as this (for example)
// OneWire ds[] = {19,14,15}
// OneWire ds[] = {19,15}
// OneWire ds[] = {14,15,16,17}


byte pinPower = 10;
byte pinRead = 19; //A5

float temperature_soil;

Ecods18b20 ecods18b20(&ds);

void setup() {

  Serial.begin(9600);
  pinMode(pinPower, OUTPUT);
  digitalWrite(pinPower,LOW);
  pinMode(pinRead, INPUT_PULLUP);

  ecods18b20.start(&ds);
  

  /* Test it */
  // Power the sensor
  
  //expander.digitalWrite(station.tsoil_config.pinPower,HIGH);
  digitalWrite(pinPower,HIGH);

  if(ecods18b20.get_temperature(&temperature_soil, true)==1)
  {
    Serial.print((int16_t)temperature_soil); Serial.println(F("C"));
  }
  
  digitalWrite(pinPower,LOW);
  //expander.digitalWrite(station.tsoil_config.pinPower,HIGH);

}

void loop() {

}
