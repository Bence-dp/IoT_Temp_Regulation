#include "globals.h"

// modèle principal
esp_model esp;

// états globaux
bool is_fire = false;
bool is_regulating = false;

float LOW_THRESHOLD = 20.0;
float HIGH_THRESHOLD = 22.0;

// historiques
float lumHistory[HISTORY_SIZE];
float tempHistory[HISTORY_SIZE];

// seuils par défaut (modifiables à chaud)
float TEMP_THRESHOLD = 5.0;   // °C
float LUM_THRESHOLD = 10000.0;     // intensité lumineuse
int historyIndex = 0; // index global

float LUM_LOW = 300;
float LUM_HIGH = 3500;
float TEMP_FIRE = 25.0;
