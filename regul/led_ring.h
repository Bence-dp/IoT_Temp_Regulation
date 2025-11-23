#ifndef LED_RING_H
#define LED_RING_H

#include <Adafruit_NeoPixel.h>
#include "config.h"

extern Adafruit_NeoPixel strip;

// On définit des couleurs faciles à utiliser
#define RED   strip.Color(255, 0, 0)    // Rouge pur
#define GREEN strip.Color(0, 255, 0)    // Vert pur  
#define BLUE  strip.Color(0, 0, 255)    // Bleu pur

void setupLED();
void turnOffLedRing();
void setColorLedRing(uint32_t color, int numLEDs);

#endif
