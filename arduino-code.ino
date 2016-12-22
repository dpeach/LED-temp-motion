// For an LED project that sits on my desk. Red light for high temp.
// Green light for just right temp. Blue light for cold temp. When
// PIR motion sensor detects movement the LED strip will flash
// random colors for 10 seconds and then return to the temperature.

#include <TrueRandom.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define TEMP_PIN 7
#define INTERRUPT_PIN 2
#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6
#define COLOR_STEP 1

OneWire ourWire(TEMP_PIN);
DallasTemperature sensors(&ourWire);

volatile unsigned long motionLastDetected = 0;
const int motionLag = 10000; // time to alert after motion ceases (milliseconds)
const int SampleTime = 1000;
int red_current_value;
int green_current_value;
int blue_current_value;
int red_new_value;
int green_new_value;
int blue_new_value;

void setup()
{             
  pinMode(RED_PIN, OUTPUT);   // sets the pins as output
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(INTERRUPT_PIN, INPUT);
  Serial.begin(9600); // ADDED ...
  attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), motionDetected, HIGH);
  red_new_value = TrueRandom.random(2) * 255;
  blue_new_value = TrueRandom.random(2) * 255;
  green_new_value = TrueRandom.random(2) * 255;
  red_current_value = TrueRandom.random(2) * 255;
  blue_current_value = TrueRandom.random(2) * 255;
  green_current_value = TrueRandom.random(2) * 255;
}

void loop()                 
{
  float temp;
  
  if (millis() - motionLastDetected < motionLag) // motion was detected recently, randomize LED
  {
    int delayTime = 10; //random(0);
    
    if (red_new_value > red_current_value) {
      red_current_value+=COLOR_STEP;
    } else if (red_new_value < red_current_value) {
      red_current_value-=COLOR_STEP;
    }
    analogWrite(RED_PIN, red_current_value);
    //analogWrite(RED_PIN, 255);
    //delay(delayTime);
    if (red_current_value < COLOR_STEP || red_current_value > (255 - COLOR_STEP)) {
      red_new_value = TrueRandom.random(2) * 255;
    }

    if (green_new_value > green_current_value) {
      green_current_value+=COLOR_STEP;
    } else if (green_new_value < green_current_value) {
      green_current_value-=COLOR_STEP;
    }
    analogWrite(GREEN_PIN, green_current_value);
    //analogWrite(GREEN_PIN, 0);
    //delay(delayTime);
    if (green_current_value < COLOR_STEP || green_current_value > (255 - COLOR_STEP)) {
      green_new_value = TrueRandom.random(2) * 255;
    }

    if (blue_new_value > blue_current_value) {
      blue_current_value+=COLOR_STEP;
    } else if (blue_new_value < blue_current_value) {
      blue_current_value-=COLOR_STEP;
    }
    analogWrite(BLUE_PIN, blue_current_value);
    //analogWrite(BLUE_PIN, 255);
    delay(delayTime);
    if (blue_current_value < COLOR_STEP || blue_current_value > (255 - COLOR_STEP)) {
      blue_new_value = TrueRandom.random(2) * 255;
    }
  }
  else // show temp colors
  {
    sensors.requestTemperatures();
    Serial.println(sensors.getTempFByIndex(0));
    temp = sensors.getTempFByIndex(0);
    delay(SampleTime);

    if (sensors.getTempFByIndex(0) >= 75)
    {
      analogWrite(RED_PIN, 255);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 0);
    }
    else if (sensors.getTempFByIndex(0) < 72)

    {
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 0);
      analogWrite(BLUE_PIN, 255);
    }
    else
    {
      analogWrite(RED_PIN, 0);
      analogWrite(GREEN_PIN, 255);
      analogWrite(BLUE_PIN, 0);
    }
  }
}

void motionDetected()
{
  motionLastDetected = millis();
}
