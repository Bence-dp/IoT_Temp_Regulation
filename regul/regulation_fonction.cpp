#include "regulation_fonction.h"

// Vérifie si la température dépasse le seuil haut
bool highThresholdExceeded(float temp){
  return temp > esp.highThreshold;
}

// Vérifie si la température est sous le seuil bas  
bool lowThresholdExceeded(float temp){
  return temp < esp.lowThreshold;
}

// Mode CHAUFFAGE - il fait trop froid
void startHeating(){
  setColorLedRing(BLUE, 5);      // LEDs bleues = il fait froid
  turnOffLed(SIMPLE_LED_GREEN);  // Éteint LED verte
  turnOnLed(SIMPLE_LED_RED);     // Allume LED rouge = chauffage actif
  setSpeedFan(0);                // Arrête le ventilateur
  esp.coolerState = false;       // Marque que le refroidissement est OFF
  esp.heaterState = true;        // Marque que le chauffage est ON
}

// Mode REFROIDISSEMENT - il fait trop chaud
void startCooling(float temp){
  turnOnLed(SIMPLE_LED_GREEN);   // Allume LED verte = ventilation active
  turnOffLed(SIMPLE_LED_RED);    // Éteint LED rouge
  setColorLedRing(RED, 5);       // LEDs rouges = il fait chaud
  esp.coolerState = true;        // Marque que le refroidissement est ON
  esp.heaterState = false;       // Marque que le chauffage est OFF
  
  // Si pas d'incendie, on ventile selon la température
  if (!is_fire) {
    setDynamicSpeedFan(128, temp);  // Ventile à vitesse adaptée
  } else{
    setSpeedFan(0);  // En cas d'incendie, on arrête tout
  }
}

// Calcule la vitesse du ventilateur selon à quel point il fait chaud
void setDynamicSpeedFan(int initialSpeed, float temp) {
  if (temp > esp.highThreshold) {
    // Plus il fait chaud, plus le ventilateur va vite
    int speed = initialSpeed + (int)((temp - HIGH_THRESHOLD) * 16);
    if (speed > 255) speed = 255;  // Vitesse max = 255
    setSpeedFan(speed);
  } else {
    setSpeedFan(0);  // Si c'est redevenu normal, on arrête
  }
}

// Fonction principale qui décide quoi faire selon la température
void regulation(float temp, int lum) {
  // On sauvegarde les mesures dans notre structure
  esp.temperature = temp;
  esp.luminosity = lum;
  
  // TROP CHAUD → on refroidit
  if (highThresholdExceeded(temp)) {
    esp.regulationState = true;  // On dit que la régulation est active
    startCooling(temp);          // On active le refroidissement
  }
  
  // TROP FROID → on chauffe
  else if (lowThresholdExceeded(temp)) {
    esp.regulationState = true;  // On dit que la régulation est active
    startHeating();              // On active le chauffage
  }
  
  // TEMPÉRATURE NORMALE → on fait rien
  else {
    turnOffLed(SIMPLE_LED_GREEN);  // Éteint LED verte
    turnOffLed(SIMPLE_LED_RED);    // Éteint LED rouge
    setColorLedRing(GREEN, 5);     // LEDs vertes = tout va bien
    esp.coolerState = false;       // Plus de refroidissement
    esp.heaterState = false;       // Plus de chauffage
    esp.regulationState = false;   // Régulation inactive
    setSpeedFan(0);                // Ventilateur arrêté
  }
}
