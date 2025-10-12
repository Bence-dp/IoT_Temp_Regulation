#ifndef SERIAL_HANDLER_H
#define SERIAL_HANDLER_H

#include <Arduino.h>

// Déclaration des variables globales externes
extern float sh;
extern float sb;

// Déclaration des fonctions
void updateFromSerial();
void setupSerial();

#endif