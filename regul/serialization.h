#ifndef SERIALIZATION_H
#define SERIALIZATION_H

#include <Arduino.h>
#include <ArduinoJson.h>
#include "model.h"

String serialize(esp_model *em);

#endif
