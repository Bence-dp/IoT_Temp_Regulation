#ifndef GLOBALS_H
#define GLOBALS_H

#include <Arduino.h>
#include "config.h"
#include "model.h"

// === Variables globales accessibles partout ===

// modèle principal
extern esp_model esp;

// états globaux
extern bool is_fire;
extern bool is_regulating;

// seuil haut et bas de la température
extern float LOW_THRESHOLD;
extern float HIGH_THRESHOLD;

// historiques
extern float lumHistory[HISTORY_SIZE];  // historique luminosité
extern float tempHistory[HISTORY_SIZE];  // historique température
extern int historyIndex;  // index global

extern float LUM_LOW;  // luminosité minimale feu
extern float LUM_HIGH;  // luminosité maximale feu
extern float TEMP_FIRE;  // seuil température feu

extern String MQTT_TOPIC;
extern String MQTT_TOPIC_GR_A;
extern String mqtt_server;
extern int MQTT_TIMING;
extern int DISTANCE

#endif
