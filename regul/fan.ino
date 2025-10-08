#include "config.h"

void setupFan() {
  pinMode(FANPIN, OUTPUT);
  analogWrite(FANPIN, 0); // arrêt
}

void setSpeedFan(int val) {
  analogWrite(FANPIN, val);
}
