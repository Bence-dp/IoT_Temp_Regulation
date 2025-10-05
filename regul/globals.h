#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "model.h"

// === Variables globales accessibles partout ===

// modèle principal
extern esp_model esp;

// états globaux
extern bool is_fire;
extern bool is_regulating;


#endif
