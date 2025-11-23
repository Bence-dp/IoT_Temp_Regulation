#ifndef REGULATION_FONCTION_H
#define REGULATION_FONCTION_H

#include <Arduino.h>
#include "config.h"
#include "globals.h"
#include "led_ring.h"
#include "fan.h"
#include "simple_led.h"

bool highThresholdExceeded(float temp);
bool lowThresholdExceeded(float temp);
void startHeating();
void startCooling(float temp);
void setDynamicSpeedFan(int initialSpeed, float temp);
void regulation(float temp, int lum);

#endif
