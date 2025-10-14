#include "globals.h"

// modèle principal
esp_model esp;

// états globaux
bool is_fire = false;
bool is_regulating = false;

float LOW_THRESHOLD = 18.0;
float HIGH_THRESHOLD = 25.0;

// historiques
float lumHistory[HISTORY_SIZE];
float tempHistory[HISTORY_SIZE];


int historyIndex = 0; // index global

float LUM_LOW = 300;
float LUM_HIGH = 3500;
float TEMP_FIRE = 35.0;
