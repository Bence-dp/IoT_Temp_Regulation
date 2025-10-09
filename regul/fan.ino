#include "config.h"

void setupFan() {
  pinMode(FANPIN, OUTPUT);
  analogWrite(FANPIN, 0); // arrêt
  esp.fanSpeed = 0;
}

void setSpeedFan(int val) {
  analogWrite(FANPIN, val);
  esp.fanSpeed = val;
}
