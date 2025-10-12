#include "config.h"

// Prépare les deux petites LEDs pour qu'elles puissent s'allumer
void setupSimpleLEDS() {
  pinMode(SIMPLE_LED_GREEN, OUTPUT);  // La LED verte est prête à s'allumer
  pinMode(SIMPLE_LED_RED, OUTPUT);    // La LED rouge est prête à s'allumer
}

// Allume une LED (verte ou rouge)
void turnOnLed(int led_pin) {
  digitalWrite(led_pin, HIGH);  // Envoie du courant à la LED
}

// Éteint une LED (verte ou rouge)
void turnOffLed(int led_pin) {
  digitalWrite(led_pin, LOW);   // Coupe le courant à la LED
}