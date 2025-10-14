#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include "model.h"
#include "globals.h"
#include "serial_handler.h"  // Pour pouvoir changer les réglages via le port série

// ==== Déclaration des fonctions ====
void initStaticInfo(esp_model &esp);
void setupSimpleLEDS();
void setupLED();
void setupTemp();
void setupFan();
void setupLum();
void regulation(float temp, int lum);
String serialize(esp_model *em);
float getLum();
float getTemp();

//================ SETUP ET LOOP ==========================

void setup() {
  // On ouvre la communication avec l'ordinateur
  Serial.begin(9600);
  
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
  Serial.println(serialize(&esp));
  
  // On attend 2 secondes avant de recommencer
  delay(2000);
}