#include "globals.h"

// === Variables globales accessibles partout ===

// modèle principal
esp_model esp;

// états globaux
bool is_fire = false;
bool is_regulating = false;

// seuil haut et bas de la température
float LOW_THRESHOLD = 18.0;
float HIGH_THRESHOLD = 25.0;

// historiques
float lumHistory[HISTORY_SIZE];  // historique luminosité
float tempHistory[HISTORY_SIZE];  // historique température
int historyIndex = 0;  // index global

float LUM_LOW = 300;  // luminosité minimale feu
float LUM_HIGH = 3500;  // luminosité maximale feu
float TEMP_FIRE = 35.0;  // seuil température feu

String MQTT_TOPIC = "uca/iot/master";
String MQTT_TOPIC_GR_A = "uca/iot/master/GR_A";

// String mqtt_server = "192.168.1.101"; 
// String mqtt_server = "public.cloud.shiftr.io"; // Failed in 2021
// need login and passwd (public,public) mqtt://public:public@public.cloud.shiftr.io
// String mqtt_server = "broker.hivemq.com"; // anynomous Ok in 2021 
// String mqtt_server = "mqtt.eclipseprojects.io"; // anynomous Ok in 2021
// String mqtt_server = "192.168.19.211";
String mqtt_server = "10.0.1.58";
// String mqtt_server = "mqtt.claveille.fr";

int MQTT_TIMING = 5;
int DISTANCE = 10;
