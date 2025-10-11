
// Initialisation des historiques
void initHistory() {
  for (int i = 0; i < HISTORY_SIZE; i++) {
    tempHistory[i] = 0.0f;
    lumHistory[i]  = 0.0f;
  }
  historyIndex = 0;  // index global
  pinMode(FIRE_LED_PIN, OUTPUT);
  digitalWrite(FIRE_LED_PIN, LOW);
  is_fire = false;
  esp.fireDetected = false;
}

// Moyenne d’un tableau sur les valeurs valides
float averageValid(float *arr) {
  int count = min(historyIndex, HISTORY_SIZE); // nombre de valeurs valides
  if (count == 0) return 0.0f;                 // éviter division par 0
  float sum = 0.0f;
  for (int i = 0; i < count; i++) sum += arr[i];
  return sum / count;
}

// Mise à jour des historiques
void updateHistory(float temp, float lum) {
  int index = historyIndex % HISTORY_SIZE; // calcul circulaire
  tempHistory[index] = temp;
  lumHistory[index]  = lum;
  historyIndex++; // incrémente l’index global
}

// Détection du feu
bool detectFire(float temp, float lum) {
    float avgTemp = averageValid(tempHistory); // moyenne des températures valides

    bool tempHigh = (avgTemp > TEMP_FIRE);
    bool lumExtreme = (lum < LUM_LOW || lum > LUM_HIGH);

    if (tempHigh && lumExtreme) {
        is_fire = true;
        esp.fireDetected = true;
        digitalWrite(FIRE_LED_PIN, HIGH);
        esp.coolerState = false;
        esp.heaterState = false;
        esp.regulationState = false;
        turnOffLed(SIMPLE_LED_RED);
        turnOffLed(SIMPLE_LED_GREEN);
        setSpeedFan(0);
    } else {
        is_fire = false;
        esp.fireDetected = false;
        digitalWrite(FIRE_LED_PIN, LOW);
    }

    return is_fire;
}
