#include "fire_detection.h"

// Prépare la mémoire pour stocker l'historique des mesures
void initHistory() {
  // Remet tous les historiques à zéro
  for (int i = 0; i < HISTORY_SIZE; i++) {
    tempHistory[i] = 0.0f;  // Efface l'historique des températures
    lumHistory[i]  = 0.0f;  // Efface l'historique des luminosités
  }
  historyIndex = 0;  // On recommence à compter depuis le début
  
  // Prépare la LED d'alarme incendie
  pinMode(FIRE_LED_PIN, OUTPUT);
  digitalWrite(FIRE_LED_PIN, LOW);  // Éteint la LED d'alarme
  
  // Remet tout en état normal
  is_fire = false;           // Pas d'incendie détecté
  esp.fireDetected = false;  // On note qu'il n'y a pas de feu
}

// Calcule la moyenne des valeurs valides dans un tableau
float averageValid(float *arr) {
  // Compte combien de mesures valides on a (au début, moins de HISTORY_SIZE)
  int count = min(historyIndex, HISTORY_SIZE);
  if (count == 0) return 0.0f;  // Évite de diviser par zéro
  
  // Additionne toutes les valeurs
  float sum = 0.0f;
  for (int i = 0; i < count; i++) sum += arr[i];
  
  // Retourne la moyenne
  return sum / count;
}

// Ajoute une nouvelle mesure à l'historique
void updateHistory(float temp, float lum) {
  // Trouve la position où écrire (tourne en rond dans le tableau)
  int index = historyIndex % HISTORY_SIZE;
  
  // Stocke les nouvelles mesures
  tempHistory[index] = temp;
  lumHistory[index]  = lum;
  
  historyIndex++;  // Avance d'une position pour la prochaine fois
}

// Vérifie s'il y a un incendie en fonction des mesures
bool detectFire(float temp, float lum) {
    // Calcule la température moyenne récente
    float avgTemp = averageValid(tempHistory);

    // Conditions pour détecter un feu :
    bool tempHigh = (avgTemp > TEMP_FIRE);  // Température trop élevée
    bool lumExtreme = (lum < LUM_LOW || lum > LUM_HIGH);  // Luminosité anormale

    // Si les deux conditions sont réunies -> ALARME INCENDIE
    if (tempHigh && lumExtreme) {
        is_fire = true;
        esp.fireDetected = true;
        digitalWrite(FIRE_LED_PIN, HIGH);  // Allume la LED d'alarme
        
        // Coupe tous les systèmes pour sécurité
        esp.coolerState = false;
        esp.heaterState = false;
        esp.regulationState = false;
        turnOffLed(SIMPLE_LED_RED);
        turnOffLed(SIMPLE_LED_GREEN);
        setSpeedFan(0);  // Arrête le ventilateur
    } else {
        // Tout est normal, on éteint l'alarme
        is_fire = false;
        esp.fireDetected = false;
        digitalWrite(FIRE_LED_PIN, LOW);  // Éteint la LED d'alarme
    }

    return is_fire;
}
