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

// === Historique ===
extern float lumHistory[HISTORY_SIZE];   // historique luminosité
extern float tempHistory[HISTORY_SIZE];  // historique température

// === Seuils dynamiques ===
extern float TEMP_THRESHOLD;   // écart de température
extern float LUM_THRESHOLD;      // écart de luminosité

extern int historyIndex;
extern float LUM_LOW;       // luminosité minimale feu
extern float LUM_HIGH;      // luminosité maximale feu
extern float TEMP_FIRE;   // seuil température feu

#endif // GLOBALS_H
