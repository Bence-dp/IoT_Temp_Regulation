#ifndef FIRE_DETECTION_H
#define FIRE_DETECTION_H

#include <Arduino.h>
#include "config.h"
#include "globals.h"
#include "simple_led.h"
#include "fan.h"

void initHistory();
float averageValid(float *arr);
void updateHistory(float temp, float lum);
bool detectFire(float temp, float lum);

#endif
