void regulation(float temp, int lum) {
  Serial.print("Regulation - Temp: ");
  Serial.print(temp);
  Serial.print(" | Lum: ");
  Serial.println(lum);

  // Exemple test
  if (temp > 30) {
    turnOnLed(19);
    turnOffLed(21);
    setColorLedRing(RED,4);
    setSpeedFan(255);
  } 
  else if (temp > 20) {
    turnOffLed(21);
    turnOffLed(19);
    setColorLedRing(GREEN,4);
    setSpeedFan(128);
  } 
  else {
    setColorLedRing(BLUE,4);
    turnOffLed(21);
    turnOnLed(19);
    setSpeedFan(0);
  }
}
