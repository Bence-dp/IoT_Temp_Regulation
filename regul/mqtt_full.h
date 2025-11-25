#ifndef MQTT_FULL_H
#define MQTT_FULL_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "wifi_utils.h"

#define MQTT_TOPIC "uca/iot/master"

extern WiFiClient espClient;
extern PubSubClient mqttclient;

void mqtt_setup();
void mqtt_pubcallback(char* topic, byte* payload, unsigned int length);
void mqtt_subscribe_mytopics();



#endif