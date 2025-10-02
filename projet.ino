#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "OneWire.h"
#include "DallasTemperature.h"


#define LED_PIN 13

#define SIMPLE_LED1 19
#define SIMPLE_LED2 21 



//================= SIMPLE LED GESTION ===================
void setupSimpleLEDS() {
  pinMode(SIMPLE_LED1, OUTPUT);
  pinMode(SIMPLE_LED2, OUTPUT);

}

void turnOnLed(int led_pin){
  digitalWrite(led_pin, HIGH);
}

void turnOffLed(int led_pin){
    digitalWrite(led_pin, LOW);
}
//==================== LED Ring ============================

#define RED strip.Color(255,0,0)
#define BLUE strip.Color(0,0,255)
#define GREEN strip.Color(0,255,0)
Adafruit_NeoPixel strip(5, LED_PIN, NEO_GRB + NEO_KHZ800);

void turnOffLedRing (){
    for (int i = 0; i < 4; i++) strip.setPixelColor(i, strip.Color(0, 0, 0)); 
    strip.show();

}

void setColorLedRing (uint32_t color){
    for (int i = 0; i < 4; i++) strip.setPixelColor(i,color); 
    strip.show();

}

void setupLED() {

  strip.begin();
  turnOffLedRing();
}


// ====================== Temperature DS18B20 ======================
#define ONE_WIRE_BUS 23
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

void setupTemp() {
  tempSensor.begin();
  Serial.println("DS18B20 ready");
}

float loopTemp() {
  float t;
  tempSensor.requestTemperaturesByIndex(0);
  t = tempSensor.getTempCByIndex(0);
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" C");
  return t;
}

// ====================== Capteur de luminosité ======================
#define LUX_PIN A5

void setupLum() {
  Serial.println("Light sensor ready");
}

int loopLum() {
  int sensorValue = analogRead(LUX_PIN); 
  Serial.print("Luminosity: ");
  Serial.println(sensorValue);
  delay(1000);
  return sensorValue;
}

// ========================= Ven PWM =================================

#define FANPIN 27

void setupFan() {
  pinMode(FANPIN, OUTPUT);
  analogWrite(FANPIN, 0); //arret
}

void setSpeedFan (int val){
  analogWrite(FANPIN, val);
}

// ======================== Values Analyse ==========================

void regulation(float temp, int lum){

}

/* string serialize(float temp, int lum){

Blachon api

}
 */
// ====================== Setup et Loop principaux ======================

void setup() {
  setupSimpleLEDS();
  setupLED();
  setupTemp();
  setupFan();
  setupLum();
}

void loop() {

  int sensorValue = loopLum();
  float tempValue =   loopTemp();
  //serialize()
  ragulation(tempValue,sensorValue);
  delay(10000);


}
