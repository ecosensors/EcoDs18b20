# EcoDs18b20
 
 Library for the DS18B20 sensors, WITHOUT WARRANTY.
 You will need a pull-up resistor of about 4.7 KOhm between the 1-Wire data line and the 3.3V

 Improvement will be done later :)


## TODO:

Calibrating the value with Compensated value

```
float ds18b20_corrected(float *temperature, float rawLow, float referenceLow, float rawRange, float referenceRange){}
```

* float rawLow          => Measure the temperatire of the ice with the DS18B20
* float referenceLow    => Measure the temprature of the ice with a reference accurate termometer
* float rawRange        => Measure the temperatire of the boiled water with the DS18B20
* float referenceRange  => Measure the temperatire of the boiled water with a reference accurate termometer
