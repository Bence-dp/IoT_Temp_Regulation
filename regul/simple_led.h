#ifndef SIMPLE_LED_H
#define SIMPLE_LED_H

#include <Arduino.h>
#include "config.h"

void setupSimpleLEDS();
void turnOnLed(int led_pin);
void turnOffLed(int led_pin);

#endif
