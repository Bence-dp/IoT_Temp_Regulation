#include <Arduino.h>
#include <WiFi.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "model.h"
#include "globals.h"
#include "serial_handler.h"  // Pour pouvoir changer les réglages via le port série
#include "wifi_utils.h"
#include "wifi_setup.h"
#include "routes.h"
#include <LittleFS.h>
#include "ESPAsyncWebServer.h"
#include "AsyncTCP.h"
#include "FS.h"
#include "simple_led.h"
#include "led_ring.h"
#include "temperature.h"
#include "fan.h"
#include "luminosite.h"
#include "fire_detection.h"
#include "regulation_fonction.h"
#include "serialization.h"


//================ SETUP ET LOOP ==========================
AsyncWebServer server(80);

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
}

void loop() {
  // D'abord, on vérifie si l'utilisateur a envoyé des commandes
  // (comme changer les températures de seuil)
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
  

  // On envoie toutes les infos à l'ordinateur
  // Update uptime (seconds since boot)
  unsigned long uptime_seconds = millis() / 1000UL;
  esp.uptime = String(uptime_seconds);
  Serial.println(serialize(&esp));

  
  // On attend le temps donné par l'utilisateur (Sampling Period) avant de recommencer
  sendReportNow();
  delay(esp.target_sp * 1000);
}