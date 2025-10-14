#include "config.h"

// Prépare le ventilateur pour qu'on puisse le contrôler
void setupFan() {
  pinMode(FANPIN, OUTPUT);      // Dit à l'ESP32 "cette broche contrôle le ventilateur"
  analogWrite(FANPIN, 0);       // Arrête le ventilateur au départ
  esp.fanSpeed = 0;             // Note que le ventilateur est à l'arrêt
}

// Change la vitesse du ventilateur
void setSpeedFan(int val) {
  analogWrite(FANPIN, val);     // Donne une vitesse au ventilateur (0-255)
  esp.fanSpeed = val;           // Retient la vitesse actuelle dans la mémoire
}