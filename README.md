# EcoDs18b20
 
 Library for the DS18B20, under development and without guarantee. Update will come later

 For now, it only works for one sensor

It's based on the following code [See more](https://www.carnetdumaker.net/articles/mesurer-une-temperature-avec-un-capteur-1-wire-ds18b20-et-une-carte-arduino-genuino/)

```
#include <OneWire.h>

const byte BROCHE_ONEWIRE = ds18b20_read;

OneWire ds(BROCHE_ONEWIRE);

  // Code de retour de la fonction getTemperature()
  enum DS18B20_RCODES {
    READ_OK,  // Lecture ok
    NO_SENSOR_FOUND,  // Pas de capteur
    INVALID_ADDRESS,  // Adresse reçue invalide
    INVALID_SENSOR  // Capteur invalide (pas un DS18B20)
  };

  if (get_TemperatureSoil(&temperature_soil, true) != READ_OK) 
  {
  	// Error
  }
  else
  {
  	// Well done
  }

/*
* It's better to power on the sensor only during measure. Wait about 750ms before taking a measure
/*

  byte get_TemperatureSoil(float *temperature_soil, byte reset_search)
{
    Serial.println(F("\r\nTemperature Soil"));
    Serial.println(F("******************************"));
    
    digitalWrite(ds18b20_pwd, HIGH); // ds18b20_pwd is the pin which power the sensor
   
    delay(750);

    byte data[9], addr[8];
      // data[] : Données lues depuis le scratchpad
      // addr[] : Adresse du module 1-Wire détecté  
      // Reset le bus 1-Wire ci nécessaire (requis pour la lecture du premier capteur)
      if (reset_search) {
        ds.reset_search();
      }

      // Recherche le prochain capteur 1-Wire disponible
      if (!ds.search(addr)) {
        // Pas de capteur
        #if defined(PCF) || defined(PCFlib)
          #if defined(PCFlib)
            expander.digitalWrite(ds18b20_pwd,LOW);
          #else
            pcf8574.digitalWrite(ds18b20_pwd,LOW);
          #endif
        #else
          digitalWrite(ds18b20_pwd, LOW);
        #endif
        
        return NO_SENSOR_FOUND;
      }   
      
      // Vérifie que l'adresse a été correctement reçue 
      if (OneWire::crc8(addr, 7) != addr[7])
      {
        // Adresse invalide
        #if defined(PCF) || defined(PCFlib)
          #if defined(PCFlib)
            expander.digitalWrite(ds18b20_pwd,LOW);
          #else
            pcf8574.digitalWrite(ds18b20_pwd,LOW);
          #endif
        #else
          digitalWrite(ds18b20_pwd, LOW);
        #endif
        return INVALID_ADDRESS;
      }

      // Vérifie qu'il s'agit bien d'un DS18B20 
      if (addr[0] != 0x28)
      {
        // Mauvais type de capteur
        #if defined(PCF) || defined(PCFlib)
          #if defined(PCFlib)
            expander.digitalWrite(ds18b20_pwd,LOW);
          #else
            pcf8574.digitalWrite(ds18b20_pwd,LOW);
          #endif
        #else
          digitalWrite(ds18b20_pwd, LOW);
        #endif
        return INVALID_SENSOR;
      }

      // Reset le bus 1-Wire et sélectionne le capteur
      ds.reset();
      ds.select(addr);
    
      // Lance une prise de mesure de température et attend la fin de la mesure
      ds.write(0x44, 1);
      delay(800);
    
      // Reset le bus 1-Wire, sélectionne le capteur et envoie une demande de lecture du scratchpad
      ds.reset();
      ds.select(addr);
      ds.write(0xBE);
   
      // Lecture du scratchpad
      for (byte i = 0; i < 9; i++) {
      data[i] = ds.read();
    }
     
    // Calcul de la température en degré Celsius 
    *temperature_soil = (int16_t) ((data[1] << 8) | data[0]) * 0.0625;

    // Pas d'erreur
    digitalWrite(ds18b20_pwd, LOW);  //turn off
    
    return READ_OK;
  #endif
}

```


TODO:

* Add corrected value into the library

```
float ds18b20_corrected(float *temperature, float rawLow, float referenceLow, float rawRange, float referenceRange){}
```

