# EcoDs18b20
 
 The library has been tested for the ATSAMD21G18 ARM Cortex M0 at 48Mhz board with 3V3 logic and it is distributed WITHOUT WARRANTY.

 That simple library allow you to work with up to 5 DS18B20 sensors which are not on the same bus. You will be able to define the data line pin, the power pin for each sensors tanks to a configurtion file. The power pin will let you to power on the sensor(s) only during a measure.

 Additionnaly, you will be able to calibrate the sensors.
 
 You will need a pull-up resistor of about 4.7 KOhm between the 1-Wire data line and the 3.3V



## Temperature with a compensated value

 To able to correct the rawValue (the value measured with the sensor), you should previously measure with the sensor, the temperature of the ice water (env.0°) and the boiled water (env. 97°, it depends on the atmospheric pressure) in order to record the values as 'referenceLow' and 'referenceMax'

```
float corrected = ecods18b20.corrected(float *rawValue, float rawLow, float referenceLow, float rawRange, float referenceRange)
```

* float rawValue        => the temperature return by the DS18B20 sensor
* float rawLow          => Mesured temperature of the iced wather with the DS18B20
* float rawMax		    => Measured temperature of boiled water with the DS18B20
* float referenceLow	=> Measured temperature of the iced wather with the an accurate termometer
* float referenceMax	=> Measured temperature of the boiled wather with the an accurate termometer
* float rawRange        => Result of the rawMax - rawMin 
* float referenceRange  => Result of the referenceMax - referenceLow
