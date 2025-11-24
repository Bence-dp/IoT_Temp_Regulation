#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <Arduino.h>
#include <DallasTemperature.h>
#include <OneWire.h>
#include "config.h"

void setupTemp();
float getTemp();

#endif
