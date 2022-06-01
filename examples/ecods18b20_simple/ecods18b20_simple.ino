#include <OneWire.h>
#include <Ecods18b20.h>

OneWire ds(19); // read the sensors at the pin19 (A1)
byte pinPower=10;
byte pinRead=19; //A1

Ecods18b20 ecods18b20;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  ecods18b20.start(&ds);
  pinMode(pinPower, OUTPUT);
  digitalWrite(pinPower,LOW);
  pinMode(pinRead, INPUT_PULLUP);

  float temperature_soil;

  // Test it
  // Power the sensor
  //expander.digitalWrite(station.tsoil_config.pinPower,HIGH)
  digitalWrite(pinPower,HIGH);
  if(ecods18b20.get_temperature(&temperature_soil, true)==1)
  {
    Serial.print((int16_t)temperature_soil); Serial.println(F("C"));
  }
  digitalWrite(pinPower,LOW);
  //expander.digitalWrite(station.tsoil_config.pinPower,HIGH)

}

void loop() {
  // put your main code here, to run repeatedly:

}
