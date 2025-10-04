#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>

// ==== prototypes ====
void setupSimpleLEDS();
void setupLED();
void setupTemp();
void setupFan();
void setupLum();
void regulation(float temp, int lum);
int loopLum();
float loopTemp();

void setup() {
  Serial.begin(9600);
  setupSimpleLEDS();
  setupLED();
  setupTemp();
  setupFan();
  setupLum();
}

void loop() {
  int lumValue = loopLum();
  float tempValue = loopTemp();
  regulation(tempValue, lumValue);
  delay(10000);
}
