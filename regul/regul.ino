#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "model.h"



esp_model esp;

// ==== prototypes ====
void initStaticInfo(esp_model &esp);
void setupSimpleLEDS();
void setupLED();
void setupTemp();
void setupFan();
void setupLum();
void regulation(float temp, int lum);
String serialize(esp_model *em);
int loopLum();
float loopTemp();



//================ SETUP ET LOOP ==========================
void setup() {
  Serial.begin(9600);
  initStaticInfo(esp);
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
