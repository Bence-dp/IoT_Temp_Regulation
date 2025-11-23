#include "led_ring.h"

Adafruit_NeoPixel strip = Adafruit_NeoPixel(5, LED_PIN, NEO_GRB + NEO_KHZ800);

void setupLED() {
  strip.begin();           // On démarre le ruban LED
  turnOffLedRing();        // On l'éteint au départ
}

void turnOffLedRing() {
  // On éteint toutes les LEDs une par une
  for (int i = 0; i < 5; i++) strip.setPixelColor(i, 0);
  strip.show();  // On envoie la commande d'extinction
}

void setColorLedRing(uint32_t color, int numLEDs) {
  // On allume le nombre de LEDs demandé avec la couleur choisie
  for (int i = 0; i < numLEDs; i++) strip.setPixelColor(i, color);
  strip.show();  // On applique les changements
}
