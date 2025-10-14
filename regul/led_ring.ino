#include "config.h"

// On crée un ruban de 5 LEDs connecté à la broche LED_PIN
Adafruit_NeoPixel strip(5, LED_PIN, NEO_GRB + NEO_KHZ800);

// On définit des couleurs faciles à utiliser
#define RED   strip.Color(255, 0, 0)    // Rouge pur
#define GREEN strip.Color(0, 255, 0)    // Vert pur  
#define BLUE  strip.Color(0, 0, 255)    // Bleu pur

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
