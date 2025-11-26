#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "AsyncTCP.h"
#include <DallasTemperature.h>
#include "ESPAsyncWebServer.h"
#include "FS.h"
#include <OneWire.h>
#include <LittleFS.h>
#include <WiFi.h>

#include "fan.h"
#include "fire_detection.h"
#include "globals.h"
#include "led_ring.h"
#include "luminosite.h"
#include "model.h"
#include "regulation_fonction.h"
#include "routes.h"
#include "serial_handler.h"
#include "serialization.h"
#include "simple_led.h"
#include "temperature.h"
#include "wifi_utils.h"
#include "wifi_setup.h"
#include "mqtt_full.h"

AsyncWebServer server(80);

//================ SETUP ET LOOP ==========================

void setup() {
  // On ouvre la communication avec l'ordinateur
  Serial.begin(9600); 
  while(!Serial); //wait for a serial connection  
  bool connectsetup = wifi_setup();
  
  // On prépare notre objet qui stocke toutes les infos
  initStaticInfo(esp);
  
  // On initialise tous nos composants :
  setupSimpleLEDS();  // Les petites LEDs témoins
  setupLED();         // Les rubans LED colorés
  setupTemp();        // Le capteur de température
  setupFan();         // Le ventilateur
  setupLum();         // Le capteur de lumière
  
  // On prépare la mémoire pour garder l'historique des mesures
  initHistory();

  // Initialize LittleFS
  if(!LittleFS.begin(true)){
    Serial.println("An Error has occurred while mounting LittleFS");
    return;
  }

  // Setup routes of the ESP Web server
  setup_http_routes(&server);
  
  // Start ESP Web server
  server.begin();

  // Setup MQTT
  mqtt_setup();
  // Try to connect and subscribe to topics right after setup
  mqtt_subscribe_mytopics();
}

void loop() {
  // D'abord, on vérifie si l'utilisateur a envoyé des commandes via Serial
  updateFromSerial();

  // On lit les capteurs
  float luminosite = getLum();    // Combien de lumière ?
  float temperature = getTemp();  // Quelle température ?

  // On règle le ventilateur et les LEDs selon les mesures
  regulation(temperature, luminosite);
  
  // On sauvegarde les mesures pour voir l'évolution dans le temps
  updateHistory(temperature, luminosite);
  
  // On vérifie s'il y a un risque d'incendie
  detectFire(temperature, luminosite);
  
  // Update uptime (seconds since boot)
  unsigned long uptime_seconds = millis() / 1000UL;
  esp.uptime = String(uptime_seconds);

  // On envoie toutes les infos à l'ordinateur
  Serial.println(serialize(&esp));
  sendReportNow();

  // Ensure MQTT is connected and process network events
  if (!mqttclient.connected()) {
    // try to (re)connect and subscribe
    mqtt_subscribe_mytopics();
  } else {
    // let the client maintain keepalive and process callbacks
    mqttclient.loop();
  }

  // On envoie toutes les infos au broker MQTT
  mqttclient.setBufferSize(2048);
  bool published = mqttclient.publish(MQTT_TOPIC, serialize(&esp).c_str());
  if (published) {
    Serial.println("Sent to MQTT");
  } else {
    Serial.println("MQTT publish failed");
  }
  bool published2 = mqttclient.publish(MQTT_TOPIC_GR_A, serialize(&esp).c_str());
  if (published2) {
    Serial.println("Sent to MQTT GR_A");
  } else {
    Serial.println("MQTT GR_A publish failed");
  }

  // On attend le temps donné par l'utilisateur (Sampling Period) avant de recommencer la boucle
  delay(esp.target_sp * 1000);
}
