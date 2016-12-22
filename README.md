# LED-temp-motion

This is for an LED project that sits on my desk. Red light for high temp. Green light for just right temp. Blue light for cold temp. When PIR motion sensor detects movement from someone coming down the hall to my office the LED strip will flash random colors for 10 seconds and then return to the temperature display.

I have put this into an ATmega168, but it can easily be controlled by an Arduino. It is Arduino code running on the ATmega chip. The ATmega168 provides a smaller package (with the added pain of actually programming it each time I want to make a change to the code). 

##Libraries Needed##

TrueRandom
OneWire
DallasTemperature

##How it works##

The default state of the LEDs is on and showing a color related to a temperature. Then when there is motion detected the LEDs randomly fade through different colors until a certain time of no motion has elapsed.

##My Parts##

* The LEDs are a short strip of RGB LEDs
* Temp sensor is a Dallas OneWire DS18B20. This project can easily be adapted to a different type of sensor. This one happens to be digital and needs the OneWire as well as the DallasTemperature libraries. But an analog sensor could be used or another digital sensor.
* PIR sensor. Not sure brand or model, but as long as it triggers the Arduino that motion has been detected, it should work.
