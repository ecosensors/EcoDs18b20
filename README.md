# EcoDs18b20
 
 Library for the DS18B20 sensors is distributed WITHOUT WARRANTY.

 That simple library allow you to work with up to 5 DS18B20 sensors which are not on the same bus. You will be able to define the data line pin, the power pin for each sensors tanks to a configurtion file. The power pin will let you to power on the sensor(s) only during a measure.

 Additionnaly, you will be able to calibrate the sensors.
 
 You will need a pull-up resistor of about 4.7 KOhm between the 1-Wire data line and the 3.3V

 Improvement will be done very soon :)


## Temperature with a compensated value

```
float ecods18b20.corrected(float *temperature, float rawLow, float referenceLow, float rawRange, float referenceRange){}
```

* temperature           => the temperature return by the DS18B20 sensor
* float rawLow          => Measure the temperatire of the ice with the DS18B20
* float referenceLow    => Measure the temprature of the ice with a reference accurate termometer
* float rawRange        => Measure the temperatire of the boiled water with the DS18B20
* float referenceRange  => Measure the temperatire of the boiled water with a reference accurate termometer
