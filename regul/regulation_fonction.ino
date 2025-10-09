#include "config.h"

bool highThresholdExceeded(float temp){
  return temp > HIGH_THRESHOLD;
}

bool lowThresholdExceeded(float temp){
  return temp < LOW_THRESHOLD;
}

void startHeating(){
  setColorLedRing(BLUE, 5);
  turnOffLed(SIMPLE_LED_GREEN);
  turnOnLed(SIMPLE_LED_RED);
  setSpeedFan(0);
  esp.coolerState = false;
  esp.heaterState = true;
}

void startCooling(float temp){
  turnOnLed(SIMPLE_LED_GREEN);
  turnOffLed(SIMPLE_LED_RED);
  setColorLedRing(RED, 5);
  esp.coolerState = true;
  esp.heaterState = false;
  if (!is_fire){
    setDynamicSpeedFan(128, temp);
  }
  else{
    setSpeedFan(0);
  }
}

void setDynamicSpeedFan(int initialSpeed, float temp) {
  if (temp > HIGH_THRESHOLD) {
    int speed = initialSpeed + (int)((temp - HIGH_THRESHOLD) * 16);
    if (speed > 255) speed = 255;
    setSpeedFan(speed);
  }
  else {
    setSpeedFan(0);
  }
}

void regulation(float temp, int lum) {
  //Serial.print("Regulation - Temp: ");
  //Serial.print(temp);
  //Serial.print(" | Lum: ");
  //Serial.println(lum);
  esp.temperature = temp;
  esp.luminosity = lum;
  if (highThresholdExceeded(temp)) {
    esp.regulationState = true;
    startCooling(temp);

  }

  else if (lowThresholdExceeded(temp)) {
    esp.regulationState = true;
    startHeating();
  }

  else {
    turnOffLed(SIMPLE_LED_GREEN);
    turnOffLed(SIMPLE_LED_RED);
    setColorLedRing(GREEN,5);
    esp.coolerState = false;
    esp.heaterState = false;
    esp.regulationState = true;
    setSpeedFan(0);
  }

}
