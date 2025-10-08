#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "model.h"
#include "globals.h"



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
  float lumValue = getLum();
  float tempValue = getTemp();
  regulation(tempValue, lumValue);
  Serial.println(serialize(&esp));
  delay(10000);
}
