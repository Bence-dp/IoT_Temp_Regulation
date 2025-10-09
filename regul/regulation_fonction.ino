#include "config.h"

bool highThresholdExceeded(float temp){
  return temp > HIGH_THRESHOLD;
}

bool lowThresholdExceeded(float temp){
  return temp < LOW_THRESHOLD;
}

void startHeating(){
  setColorLedRing(BLUE, 4);
  turnOffLed(SIMPLE_LED_GREEN);
  turnOnLed(SIMPLE_LED_RED);
  setSpeedFan(0);
}

void startCooling(float temp){
  turnOnLed(SIMPLE_LED_GREEN);
  turnOffLed(SIMPLE_LED_RED);
  setColorLedRing(RED, 4);
  if (!is_fire){
    setDynamicSpeedFan(128, temp);
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

    startCooling(temp);

  }

  else if (lowThresholdExceeded(temp)) {
    startHeating();
  }

  else {
    turnOffLed(SIMPLE_LED_GREEN);
    turnOffLed(SIMPLE_LED_RED);
    setColorLedRing(GREEN,4);
    setSpeedFan(0);
  }

}
