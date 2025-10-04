#define FANPIN 27

void setupFan() {
  pinMode(FANPIN, OUTPUT);
  analogWrite(FANPIN, 0); // arrêt
}

void setSpeedFan(int val) {
  analogWrite(FANPIN, val);
}
