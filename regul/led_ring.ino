#include "config.h"

Adafruit_NeoPixel strip(5, LED_PIN, NEO_GRB + NEO_KHZ800);

#define RED   strip.Color(255, 0, 0)
#define GREEN strip.Color(0, 255, 0)
#define BLUE  strip.Color(0, 0, 255)

void setupLED() {
  strip.begin();
  turnOffLedRing();
}

void turnOffLedRing() {
  for (int i = 0; i < 4; i++) strip.setPixelColor(i, 0);
  strip.show();
}

void setColorLedRing(uint32_t color,int numLEDs) {
  for (int i = 0; i < numLEDs; i++) strip.setPixelColor(i, color);
  strip.show();
}
