#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "model.h"
#include "config.h"

// === Variables globales accessibles partout ===

// modèle principal
extern esp_model esp;

// états globaux
extern bool is_fire;
extern bool is_regulating;

// Seuil haut et bas de la température
extern float HIGH_THRESHOLD;
extern float LOW_THRESHOLD;

// === Historique ===
extern float lumHistory[HISTORY_SIZE];   // historique luminosité
extern float tempHistory[HISTORY_SIZE];  // historique température


extern int historyIndex;
extern float LUM_LOW;       // luminosité minimale feu
extern float LUM_HIGH;      // luminosité maximale feu
extern float TEMP_FIRE;   // seuil température feu

#endif // GLOBALS_H
