/*
 * The scrpt is procided without garranty
 * and you may need to adapt it following your needs, specially if you
 * do not use a configuration file. (There is enough comment to do it :) )
 * 
 * NOTE: Serval OneWire sensor can be on the same bus. I wrote this code to respond to my needs because my board
 * do not have a commun wire, then all sensors are not on the bus/pin. But you can adapt it esly.
 * 
 */
 
#include <OneWire.h>
#include <Ecods18b20.h>
#include "station-29.h"     // Configuration file

#define PCF                 // If you are using a PCF8574 (GPIO Port Expander)
                            // If you don't, comment it
#if defined(PCF)
  #include <Wire.h>         // Required for I2C communication
  #include "PCF8574.h"      // Required for PCF857
  PCF8574 expander;
  // I am using PCF8574 to power the DS18B20 sensors during a measure
#endif

OneWire onewire(19);        // read the sensors at the pin 19 (A1). It's require to define a pin here

// byte pinPower1=10;
// byte pinRead1=19; //A1

float temperature_soil;

Ecods18b20 ecods18b20;

void setup() {
  
  Serial.begin(9600);

  delay(9000);                        // Add a delay to have time to open the terminal and see the events

  Serial.println(F("\r\n******************************************"));
  Serial.println(F("*               DS18B20                  *"));
  Serial.println(F("*              EcoSensors                *"));
  Serial.println(F("******************************************"));
  Serial.println(station.nom);
  Serial.println();
  
  #if defined(PCF)
    Wire.begin();                     // Wire is ony needed because of the PCF8574
    Serial.println(F("# PCF8574"));
    // Igone the following lines if you are not using a PCF8574
    expander.begin(0x27);             // Start PCF8574 with it address

    for (int p = 1; p < 7; p++)
    {
      expander.pinMode(p, OUTPUT);    // Define the pin (1-6)
      expander.digitalWrite(p, LOW);  // Put pin LOW
      delay(50);
      Serial.print(p); Serial.print(F(":"));
      Serial.println(expander.digitalRead(p) ? "HIGH" : "LOW");
      delay(50);
    }
  #endif

  /*
   * // If you have other DS18B20 in another bus, 
   * // you need to setup the pinMode for those pin
   * pinMode(pinPower1, OUTPUT);
   * digitalWrite(pinPower1,LOW);
   * pinMode(pinRead1, INPUT_PULLUP);
  */

  /*
   * I am using a configuration file to configure the pin of my sensor.
   * You may not have a configuration, then comment those lines and uncomment the lines above. 
   * You can setup other pinMode
   */

    Serial.println(F("\r\n# pinMode as INPUT_PULLUP"));
    // Checking if the firt sensor is activate and set the pinMode of read pin as INPUT_PULLUP
    if(station.bud1_active == true){
        pinMode(station.bud1_config.pinRead, INPUT_PULLUP);          // (A1)
    }

    // Checking if the second sensor is activate and set the pinMode of read pin as INPUT_PULLUP
    if(station.bud2_active == true){
      pinMode(station.bud2_config.pinRead, INPUT_PULLUP);          // (A2)
    }

    // Checking if the third sensor is activate and set the pinMode of read pin as INPUT_PULLUP
    if(station.bud3_active == true){
      pinMode(station.bud3_config.pinRead, INPUT_PULLUP);          // (A3)
    }

    // Checking if the fourth sensor is activate and set the pinMode of read pin as INPUT_PULLUP
    if(station.bud4_active == true){
      pinMode(station.bud4_config.pinRead, INPUT_PULLUP);          // (A4)
    }
    
    // Checking if the last sensor is activate and set the pinMode of read pin as INPUT_PULLUP
    if(station.temperature_soil_active == true){
      pinMode(station.tsoil_config.pinRead, INPUT_PULLUP);   // (A5)
    }

  /*  
   *   Read the value of the DS18B20 sensors
   */

  /*
   * First sensor
   */
  if(station.bud1_active == true){
      Serial.println(F("\r\n# Read the sensors 1"));
      // Need to chamg for each new bus/pin
      onewire.begin(station.bud1_config.pinRead);                   // Define the new bus
      
      // Power the sensor
      #if defined(PCF)
        expander.digitalWrite(station.bud1_config.pinPower, HIGH);  // Put pin HIGH
      #else
        digitalWrite(pinPower1,HIGH);       // If you dont
      #endif

      delay(1000);
      
      // Read the value
      if(ecods18b20.get_temperature(&onewire, &temperature_soil, true)==1)
      {
        Serial.print(F("Measure: "));
        Serial.print((int16_t)temperature_soil); Serial.println(F("C"));
      }
      delay(100);
      
      // Power off the sensor
      #if defined(PCF)
        expander.digitalWrite(station.bud1_config.pinPower, LOW);  // Put pin LOW
      #else
        digitalWrite(pinPower1,LOW);       // If you dont
      #endif
  } // END if(station.bud1_active == true){

  // Copy/past and change the variables for the other sensors or check the function in the loop(); 


  // Next we will read the fourth sensor each 5 sec
  onewire.begin(station.tsoil_config.pinRead);                   // Define the new bus
}


void loop() {
  // Read the temperature of the soil each 5 second

   /*
   * Fift sensor
   */
  if(station.temperature_soil_active == true){
      Serial.println(F("\r\n# Read the sensors 5"));
      // Power the sensor
      #if defined(PCF)
        expander.digitalWrite(station.tsoil_config.pinPower, HIGH);  // Put pin HIGH
      #else
        digitalWrite(pinPower4,HIGH);       // You will ne define that pin above
      #endif

      delay(1000);
      
      // Read the value
      if(ecods18b20.get_temperature(&onewire, &temperature_soil, true)==1)
      {
        Serial.print(F("Measure: "));
        Serial.print((int16_t)temperature_soil); Serial.println(F("C"));
      }
      delay(100);
      
      // Power off the sensor
      #if defined(PCF)
        expander.digitalWrite(station.tsoil_config.pinPower, LOW);  // Put pin LOW
      #else
        digitalWrite(pinPower4,LOW);       // If you dont
      #endif
  } // END if(station.temperature_soil_active == true){
  
  delay(5000);
  temperature_soil = 0;   // (Not really needed)

}
