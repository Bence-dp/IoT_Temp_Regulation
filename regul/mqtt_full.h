#ifndef MQTT_FULL_H
#define MQTT_FULL_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>
#include "config.h"
#include "wifi_utils.h"

/*===== MQTT TOPICS ===============*/
#define MQTT_TOPIC "uca/iot/master"
#define MQTT_TOPIC_GR_A "uca/iot/master/GR_A"

/*===== ESP is a MQTT Client =======*/
extern WiFiClient espClient;
extern PubSubClient mqttclient;

void mqtt_setup();
void mqtt_pubcallback(char* topic, byte* payload, unsigned int length);
void mqtt_subscribe_mytopics();

void sendMqttReport();

#endif
